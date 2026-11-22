// Render real JUCE editor components; no image retouching. Args: output directory.
#include "PluginProcessor.h"
#include "PluginEditor.h"
#include <iostream>
#include <cstdlib>

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
        // Arp mit Tonumfang einer Floete
        for (auto [id, v] : { std::pair<const char*, float> { "umfang3", 1.0f }, { "tief3", 60.0f }, { "hoch3", 96.0f } })
            if (auto* prm = processor.apvts.getParameter (id)) prm->setValueNotifyingHost (prm->convertTo0to1 (v));
        // Szene: Fahrt nach oben, 32 Takte mit hartem Ende, gerade in Takt 6 (Einstieg Bass-Schlag)
        for (auto [id, v] : { std::pair<const char*, float> { "fahrt", 1.0f }, { "fahrtX", 0.72f }, { "fahrtY", 0.88f }, { "szenenLaenge", 4.0f }, { "ende", 0.0f } })
            if (auto* prm = processor.apvts.getParameter (id)) prm->setValueNotifyingHost (prm->convertTo0to1 (v));
        processor.sceneBar.store (5);
        processor.sceneEntry.store (stromscore::EntryBass);
        processor.pointX.store (0.26f + (0.72f - 0.26f) * 0.625f);
        processor.pointY.store (0.58f + (0.88f - 0.58f) * 0.625f);
        processor.hostPlaying.store (true);
        const int w = 4;   // "Agentenfarbe"
        processor.wendung.store (w);
        processor.chordIndex.store (1);
        processor.chordRoot.store (stromscore::kWendungen[w].ch[1].root);
        processor.chordType.store (stromscore::kWendungen[w].ch[1].type);
        processor.nextRoot.store (stromscore::kWendungen[w].ch[2].root);
        processor.nextType.store (stromscore::kWendungen[w].ch[2].type);
        processor.chordProgress.store (0.4f);
        startTimer (40);
    }
    int result = 0;
private:
    void timerCallback() override
    {
        if (index >= 7)
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
            if (index == 5)
            {
                processor.apvts.getParameter ("cc0Lo1")->setValueNotifyingHost (100.0f / 127.0f);
                processor.apvts.getParameter ("dynamikCc")->setValueNotifyingHost (1.0f);
            }
            if (index == 6)
            {
                processor.apvts.getParameter ("genre")->setValueNotifyingHost (1.0f);
                processor.genreInUse.store (stromscore::GenrePopRock); processor.wendung.store (27);
                processor.chordIndex.store (0); processor.chordRoot.store (0); processor.chordType.store (stromscore::Maj);
            }
            juce::MemoryBlock state;
            processor.getStateInformation (state);
            auto xml = juce::AudioProcessor::getXmlFromBinary (state.getData(), (int) state.getSize());
            if (! xml) { fail ("Invalid processor state"); return; }
            xml->setAttribute ("theme", index == 1 ? 1 : 0);
            xml->setAttribute ("uiW", StromscoreProcessor::kUiWidth);
            juce::AudioProcessor::copyXmlToBinary (*xml, state);
            processor.setStateInformation (state.getData(), (int) state.getSize());
            processor.publishedDriveGeneration.store (processor.driveGeneration.load());
            processor.driveProgress.store (0.625f); // same fixture position as pointX/Y above
            editor.reset (processor.createEditor());
            editor->setSize (StromscoreProcessor::kUiWidth, StromscoreProcessor::kUiHeight); editor->setVisible (true);
            return;   // Anhaenge und Timer erst auf der echten Message-Loop einschwingen lassen
        }
        if (! lit)
        {
            const float levels[stromscore::kNumOutputs] = { 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f };
            for (int i = 0; i < stromscore::kNumOutputs; ++i) processor.activity[i].store (levels[i]);
            if (index == 2) clickButton (*editor, "Bearbeiten");   // drittes Bild: eigene Akkordfolge
            if (index == 3) clickButton (*editor, "Umfang3");      // viertes Bild: Fenster fuer den Tonumfang
            if (index == 5) dynamic_cast<StromscoreEditor*> (editor.get())->showOutputCcRanges();
            if (index == 6) clickButton (*editor, "Wendungsinfo");
            if (index == 4) clickButton (*editor, "Umfang6");      // fuenftes Bild: Fenster fuer den Stich (fest auf einer Taste)
            lit = true;
            steps = 0;
            return;   // der Editor holt sich die Werte beim naechsten Takt
        }
        // Das Fenster oeffnet sich asynchron; ohne Fensterfokus (virtueller Bildschirm) schliesst JUCE es nach 0,2 s wieder.
        // Darum wird aufgenommen, sobald es da ist.
        if (index >= 3 && ! hasCallout (*editor) && settleTicks++ < 20) return;
        if (index == 4 && std::getenv ("STROMSCORE_TOGGLE_TEST") != nullptr && toggles < std::atoi (std::getenv ("STROMSCORE_TOGGLE_TEST")))   // Pruefung: im offenen Stich-Fenster hin und her schalten
        {
            clickButton (*editor, (toggles % 2 == 0) ? "Akkord" : "Fest");
            ++toggles;
            return;
        }
        if (index <= 1 && steps < 10)   // die Musik faehrt ein Stueck auf B zu: die Spur entsteht
        {
            const float f = 0.4f + 0.0225f * (float) steps++;
            processor.pointX.store (0.26f + (0.72f - 0.26f) * f);
            processor.pointY.store (0.58f + (0.88f - 0.58f) * f);
            return;
        }
        auto image = editor->createComponentSnapshot (editor->getLocalBounds(), true, 2.0f);
        static const char* names[] = { "oberflaeche-dunkel.png", "oberflaeche-hell.png", "oberflaeche-akkordfolge.png", "oberflaeche-tonumfang.png", "oberflaeche-stich.png", "oberflaeche-ccbereich.png", "oberflaeche-wendungsinfo.png" };
        auto file = output.getChildFile (names[index]);
        file.deleteFile();
        juce::FileOutputStream stream (file);
        if (! stream.openedOk() || ! juce::PNGImageFormat().writeImageToStream (image, stream))
        { fail ("Could not write screenshot"); return; }
        std::cout << file.getFullPathName() << std::endl;
        images.add (file.getFileName());
        editor.reset();
        lit = false; settleTicks = 0;
        ++index;
    }
    static bool hasCallout (juce::Component& c)
    {
        if (dynamic_cast<juce::CallOutBox*> (&c) != nullptr && c.isVisible()) return true;
        for (auto* child : c.getChildren())
            if (hasCallout (*child)) return true;
        return false;
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
    int settleTicks = 0;
    int steps = 0;
    int toggles = 0;
};

int main (int argc, char** argv)
{
    juce::ScopedJuceInitialiser_GUI initialise;
    if (argc != 2) { std::cerr << "Usage: Screenshot <output-directory>" << std::endl; return 1; }
    Capture capture (juce::File (juce::String::fromUTF8 (argv[1])));
    juce::MessageManager::getInstance()->runDispatchLoop();
    return capture.result;
}
