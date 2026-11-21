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
        // Zustand wie waehrend der Wiedergabe: dunkle, angespannte Lage, zweiter Akkord, einige Ebenen leuchten
        processor.apvts.getParameter ("faerbung")->setValueNotifyingHost (0.26f);
        processor.apvts.getParameter ("intensitaet")->setValueNotifyingHost (0.58f);
        processor.apvts.getParameter ("unruhe")->setValueNotifyingHost (0.45f);
        if (auto* bass = processor.apvts.getParameter ("intensitaet2"))   // Bass etwas dichter als das Feld
            bass->setValueNotifyingHost (bass->convertTo0to1 (0.3f));
        processor.hostPlaying.store (true);
        const int w = 4;   // "Agentenfarbe"
        processor.wendung.store (w);
        processor.chordIndex.store (1);
        processor.chordRoot.store (stromscore::kWendungen[w].ch[1].root);
        processor.chordType.store (stromscore::kWendungen[w].ch[1].type);
        processor.nextRoot.store (stromscore::kWendungen[w].ch[2].root);
        processor.nextType.store (stromscore::kWendungen[w].ch[2].type);
        processor.chordProgress.store (0.4f);
        startTimer (100);
    }
    int result = 0;
private:
    void timerCallback() override
    {
        if (index >= 3)
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
            xml->setAttribute ("theme", index == 1 ? 1 : 0);
            xml->setAttribute ("uiW", StromscoreProcessor::kUiWidth);
            juce::AudioProcessor::copyXmlToBinary (*xml, state);
            processor.setStateInformation (state.getData(), (int) state.getSize());
            editor.reset (processor.createEditor());
            editor->setSize (StromscoreProcessor::kUiWidth, StromscoreProcessor::kUiHeight); editor->setVisible (true);
            return;   // Anhaenge und Timer erst auf der echten Message-Loop einschwingen lassen
        }
        if (! lit)
        {
            const float levels[stromscore::kNumLayers] = { 1.0f, 0.0f, 1.0f, 0.0f, 0.0f };
            for (int i = 0; i < stromscore::kNumLayers; ++i) processor.activity[i].store (levels[i]);
            if (index == 2) clickButton (*editor, "Bearbeiten");   // drittes Bild: eigene Akkordfolge
            lit = true;
            return;   // der Editor holt sich die Werte beim naechsten Takt
        }
        auto image = editor->createComponentSnapshot (editor->getLocalBounds(), true, 2.0f);
        static const char* names[] = { "oberflaeche-dunkel.png", "oberflaeche-hell.png", "oberflaeche-akkordfolge.png" };
        auto file = output.getChildFile (names[index]);
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
    static bool clickButton (juce::Component& c, const char* prefix)
    {
        if (auto* b = dynamic_cast<juce::Button*> (&c))
            if (b->getButtonText().startsWith (prefix) || b->getName() == prefix) { b->triggerClick(); return true; }
        for (auto* child : c.getChildren())
            if (clickButton (*child, prefix)) return true;
        return false;
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
