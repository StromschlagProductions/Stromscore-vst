// Render real JUCE editor components; no image retouching. Args: output directory.
#include "PluginProcessor.h"
#include <iostream>

class Capture final : private juce::Timer
{
public:
    explicit Capture (juce::File destination) : output (std::move (destination))
    {
        output.createDirectory();
        processor.prepareToPlay (48000, 512);
        // Zustand wie waehrend der Wiedergabe: zweiter Akkord, einige Ebenen leuchten
        processor.apvts.getParameter ("verlauf")->setValueNotifyingHost (0.62f);
        processor.hostPlaying.store (true);
        processor.chordIndex.store (1);
        startTimer (100);
    }
    int result = 0;
private:
    void timerCallback() override
    {
        if (index >= 2)
        {
            auto* manifest = new juce::DynamicObject();
            manifest->setProperty ("version", PLUGIN_VERSION_TEXT);
            manifest->setProperty ("images", images);
            const juce::var data (manifest);
            if (! output.getChildFile ("screenshots.json").replaceWithText (juce::JSON::toString (data)))
            { fail ("Could not write screenshot manifest"); return; }
            stopTimer(); juce::MessageManager::getInstance()->stopDispatchLoop(); return;
        }
        if (! editor)
        {
            juce::MemoryBlock state;
            processor.getStateInformation (state);
            auto xml = juce::AudioProcessor::getXmlFromBinary (state.getData(), (int) state.getSize());
            if (! xml) { fail ("Invalid processor state"); return; }
            xml->setAttribute ("theme", index);
            xml->setAttribute ("uiW", 820);
            juce::AudioProcessor::copyXmlToBinary (*xml, state);
            processor.setStateInformation (state.getData(), (int) state.getSize());
            editor.reset (processor.createEditor());
            editor->setSize (820, 420); editor->setVisible (true);
            return;   // Anhaenge und Timer erst auf der echten Message-Loop einschwingen lassen
        }
        if (! lit)
        {
            const float levels[stromscore::kNumLayers] = { 1.0f, 0.0f, 1.0f, 0.0f, 0.0f };
            for (int i = 0; i < stromscore::kNumLayers; ++i) processor.activity[i].store (levels[i]);
            lit = true;
            return;   // der Editor holt sich die Werte beim naechsten Takt
        }
        auto image = editor->createComponentSnapshot (editor->getLocalBounds(), true, 2.0f);
        auto file = output.getChildFile (index == 0 ? "oberflaeche-dunkel.png" : "oberflaeche-hell.png");
        file.deleteFile();
        juce::FileOutputStream stream (file);
        if (! stream.openedOk() || ! juce::PNGImageFormat().writeImageToStream (image, stream))
        { fail ("Could not write screenshot"); return; }
        std::cout << file.getFullPathName() << std::endl;
        images.add (file.getFileName());
        editor.reset();
        lit = false;
        ++index;
    }
    void fail (const char* reason)
    {
        std::cerr << reason << std::endl; result = 1; stopTimer();
        juce::MessageManager::getInstance()->stopDispatchLoop();
    }
    StromscoreProcessor processor;
    juce::File output;
    std::unique_ptr<juce::AudioProcessorEditor> editor;
    juce::Array<juce::var> images;
    int index = 0;
    bool lit = false;
};

int main (int argc, char** argv)
{
    juce::ScopedJuceInitialiser_GUI initialise;
    if (argc != 2) { std::cerr << "Usage: Screenshot <output-directory>" << std::endl; return 1; }
    Capture capture (juce::File (juce::String::fromUTF8 (argv[1])));
    juce::MessageManager::getInstance()->runDispatchLoop();
    return capture.result;
}
