#include "PluginEditor.h"
#include <BinaryData.h>

namespace
{
juce::String u8 (const char* s) { return juce::String (juce::CharPointer_UTF8 (s)); }

const char* kLayerTitle[stromscore::kNumLayers] = { "FLÄCHE", "BASS", "ARP", "AKZENTE", "GEGENSTIMME" };
const char* kLayerTip[stromscore::kNumLayers] = {
    "Fläche: Akkorde, gehalten oder als kurze Schläge, Puls, Staccato und Gated. Gehaltene Akkorde gehen auf den Kanal für lang, alle kurzen Muster auf den für kurz. Stellst du beide auf denselben Kanal, spielt alles auf einem Instrument.",
    "Bass: Grundton der Akkorde in verschiedenen Mustern. Gehalten, Halbe und Orgelpunkt gehen auf den Kanal für lang, alle anderen Muster auf den für kurz. Stellst du beide auf denselben Kanal, spielt alles auf einem Instrument.",
    "Arp: gebrochene Akkorde und Figuren, auch als Ostinato.",
    "Akzent: gelegentliche kurze Einwürfe, nie ein stehender Ton. Der Tupfer spielt einzelne hohe Töne auf Zwischenzeiten, etwa für Celesta, Glocken oder Pizzicato. Der Stich ist ein einzelner kurzer Schlag an Akkordwechseln und am Ende der Phrase: fest auf einer Taste, etwa für eine Pauke oder große Trommel, oder auf dem Grundton des Akkords, etwa für Klavier oder einen Synth-Stab. Bei wenig Intensität spielt nur der Tupfer, mit mehr kommt der Stich dazu und antwortet. Bei Unruhe kommt ein fremder, reibender Ton in der Mitte des Akkords hinzu.",
    "Gegenstimme: die einzige lange Linie, in mittlerer Lage. Sie geht schrittweise von Akkord zu Akkord, bewegter mit mehr Intensität, bei Unruhe mit Vorhalten. Gedacht für Horn, Cello, Oboe oder ein Lead-Instrument." };
}

// ---------------------------------------------------------------- Stimmungsfeld

void MoodPad::paint (juce::Graphics& g)
{
    auto r = getLocalBounds().toFloat();
    g.setColour (panel);
    g.fillRoundedRectangle (r, 8.0f);

    const auto a = r.reduced (10.0f);
    g.setColour (line);
    g.drawRoundedRectangle (r.reduced (0.5f), 8.0f, 1.0f);

    g.setColour (line.withAlpha (0.6f));
    for (int i = 1; i < 4; ++i)
    {
        g.fillRect (a.getX() + a.getWidth() * (float) i / 4.0f - 0.5f, a.getY(), 1.0f, a.getHeight());
        g.fillRect (a.getX(), a.getY() + a.getHeight() * (float) i / 4.0f - 0.5f, a.getWidth(), 1.0f);
    }

    // Ecken: die vier Grundstimmungen
    g.setColour (dim);
    g.setFont (juce::FontOptions (11.0f));
    const int pad = 6;
    const auto ai = a.toNearestInt().reduced (pad);
    g.drawText (u8 ("Angst"), ai, juce::Justification::topLeft);
    g.drawText (u8 ("Triumph"), ai, juce::Justification::topRight);
    g.drawText (u8 ("Lauern"), ai, juce::Justification::bottomLeft);
    g.drawText (u8 ("Ruhe"), ai, juce::Justification::centredBottom);
    g.drawText (u8 ("Wärme"), ai, juce::Justification::bottomRight);

    auto toScreen = [&a] (float fx, float fy) { return juce::Point<float> (a.getX() + fx * a.getWidth(), a.getBottom() - fy * a.getHeight()); };

    const auto pa = toScreen (x, y);
    const float px = pa.x, py = pa.y;
    // Fahrt: gestrichelter Weg von A nach B, B als Ring (auch schon, wenn das Ziel nur gesetzt ist)
    if (showB || targetPending)
    {
        const auto pb = toScreen (bx, by);
        juce::Path path, dashed;
        path.startNewSubPath (px, py);
        path.lineTo (pb);
        const float dashes[] = { 4.0f, 4.0f };
        juce::PathStrokeType (1.3f).createDashedStroke (dashed, path, dashes, 2);
        g.setColour (accent.withAlpha (0.65f));
        g.fillPath (dashed);
        g.setColour (panel);
        g.fillEllipse (pb.x - 8.0f, pb.y - 8.0f, 16.0f, 16.0f);
        g.setColour (accent);
        g.drawEllipse (pb.x - 8.0f, pb.y - 8.0f, 16.0f, 16.0f, 2.0f);
        g.setFont (juce::FontOptions (10.5f, juce::Font::bold));
        g.drawText ("B", juce::Rectangle<float> (pb.x - 8.0f, pb.y - 8.0f, 16.0f, 16.0f), juce::Justification::centred);
    }

    // Die Unruhe zappelt dort, wo die Musik gerade ist: waehrend einer Fahrt am klingenden Punkt, sonst an A
    const auto live = showNow ? toScreen (nowX, nowY) : pa;
    const float radius = 9.0f + z * 24.0f;
    const bool riss = z >= stromscore::kRissStart;
    const float amp = z * 0.22f + (riss ? 0.12f * (z - stromscore::kRissStart) / (1.0f - stromscore::kRissStart) : 0.0f);
    const float phase = (float) (juce::Time::getMillisecondCounter() % 100000) * 0.004f * (0.3f + z) * (riss ? 1.8f : 1.0f);
    const auto ringColour = riss ? juce::Colour (0xffe04848) : accent;
    auto wobble = [&] (float rad, float am, float f1, float f2, float ph)
    {
        juce::Path ring;
        for (int i = 0; i <= 72; ++i)
        {
            const float t = juce::MathConstants<float>::twoPi * (float) i / 72.0f;
            const float rr = rad * (1.0f + am * std::sin (f1 * t + ph) + am * 0.5f * std::sin (f2 * t - 1.7f * ph));
            const juce::Point<float> p (live.x + rr * std::cos (t), live.y + rr * std::sin (t));
            if (i == 0) ring.startNewSubPath (p); else ring.lineTo (p);
        }
        ring.closeSubPath();
        return ring;
    };
    const auto ring = wobble (radius, amp, 7.0f, 13.0f, phase);
    g.setColour (ringColour.withAlpha (0.12f + 0.18f * z));
    g.fillPath (ring);
    g.setColour (ringColour.withAlpha (0.85f));
    g.strokePath (ring, juce::PathStrokeType (1.5f));
    // Punkt A
    g.setColour (accent);
    g.fillEllipse (px - 6.0f, py - 6.0f, 12.0f, 12.0f);
    if (showB || targetPending)   // mit Fahrt oder gesetztem Ziel ist der Punkt A beschriftet
    {
        g.setColour (juce::Colours::black);
        g.setFont (juce::FontOptions (9.5f, juce::Font::bold));
        g.drawText ("A", juce::Rectangle<float> (px - 6.0f, py - 6.0f, 12.0f, 12.0f), juce::Justification::centred);
    }
    // Wo die Musik gerade ist (waehrend einer Fahrt)
    if (showNow)
    {
        g.setColour (text);
        g.fillEllipse (live.x - 4.5f, live.y - 4.5f, 9.0f, 9.0f);
        g.setColour (panel);
        g.drawEllipse (live.x - 4.5f, live.y - 4.5f, 9.0f, 9.0f, 1.5f);
    }

    if ((showB || targetPending) && pa.getDistanceFrom (toScreen (bx, by)) <= 14.0f)
    {
        const juce::Rectangle<float> badge (px - 15.0f, py - 9.0f, 30.0f, 18.0f);
        g.setColour (accent); g.fillRoundedRectangle (badge, 5.0f);
        g.setColour (juce::Colours::black); g.setFont (juce::FontOptions (11.0f, juce::Font::bold));
        g.drawText ("A/B", badge, juce::Justification::centred);
    }

    // Feld-Karte: beim Ueberfahren die naechstgelegenen Wendungen, klein und blass
    if (numHover > 0 && ! dragging)
    {
        g.setFont (juce::FontOptions (10.0f));
        for (int i = 0; i < numHover; ++i)
        {
            const float hx = a.getX() + hover[i].x * a.getWidth(), hy = a.getY() + (1.0f - hover[i].y) * a.getHeight();
            g.setColour (text.withAlpha (i == 0 ? 0.75f : 0.45f));
            g.fillEllipse (hx - 2.0f, hy - 2.0f, 4.0f, 4.0f);
            const float tw = 96.0f;
            const float tx = juce::jlimit (a.getX(), a.getRight() - tw, hx - tw * 0.5f);
            g.drawText (hover[i].name, juce::Rectangle<float> (tx, hy + 3.0f, tw, 12.0f), juce::Justification::centred);
        }
    }
}

// ---------------------------------------------------------------- Akkord-Anzeige

void ChordDisplay::paint (juce::Graphics& g)
{
    auto r = getLocalBounds().toFloat();
    g.setColour (panel);
    g.fillRoundedRectangle (r, 6.0f);
    g.setColour (line);
    g.drawRoundedRectangle (r.reduced (0.5f), 6.0f, 1.0f);

    const int w = getWidth();
    g.setColour (playing ? text : dim);
    g.setFont (juce::FontOptions (30.0f, juce::Font::bold));
    g.drawText (playing ? chord : u8 ("–"), 14, 8, w - 28, 38, juce::Justification::centredLeft);
    g.setColour (dim);
    g.setFont (juce::FontOptions (11.0f));
    g.drawText (meter, 14, 12, w - 28, 16, juce::Justification::centredRight);
    if (playing && nextChord.isNotEmpty())
    {
        g.setFont (juce::FontOptions (13.0f));
        g.drawText (u8 ("dann ") + nextChord, 14, 28, w - 28, 16, juce::Justification::centredRight);
        g.setColour (line);
        g.fillRoundedRectangle (14.0f, 46.0f, (float) w - 28.0f, 2.0f, 1.0f);
        g.setColour (accent.withAlpha (0.8f));
        g.fillRoundedRectangle (14.0f, 46.0f, ((float) w - 28.0f) * juce::jlimit (0.0f, 1.0f, progress), 2.0f, 1.0f);
    }
    g.setColour (accent);
    g.setFont (juce::FontOptions (13.0f, juce::Font::bold));
    g.drawText (playing ? (custom ? wendung : u8 ("Wendung: ") + wendung) : u8 ("Wiedergabe starten oder VORHÖREN einschalten"), 14, 52, w - 28, 18, juce::Justification::centredLeft);

    // Woraus VARIATION an dieser Stelle waehlt
    if (candidates.isNotEmpty())
    {
        g.setColour (dim);
        g.setFont (juce::FontOptions (11.0f));
        g.drawFittedText (u8 ("Hier: ") + candidates, 14, getHeight() - 80, w - 28, 16, juce::Justification::centredLeft, 1, 0.85f);
    }

    // Stimmung live: Faerbung, Intensitaet, Unruhe in Prozent; die Balken lassen sich ziehen
    {
        const char* names[3] = { "Färbung", "Intensität", "Unruhe" };
        for (int i = 0; i < 3; ++i)
        {
            const auto bar = this->bar (i);
            const float yy = bar.getY() - 5.0f;
            g.setColour (dim);
            g.setFont (juce::FontOptions (11.0f));
            g.drawText (u8 (names[i]), juce::Rectangle<float> (14.0f, yy, kBarLabelW, 16.0f), juce::Justification::centredLeft);
            const float v = juce::jlimit (0.0f, 1.0f, mood[i]);
            g.setColour (line);
            g.fillRoundedRectangle (bar, 3.0f);
            const auto filled = bar.withWidth (juce::jmax (6.0f, bar.getWidth() * v));
            g.setColour (accent);
            g.fillRoundedRectangle (filled, 3.0f);
            if (i == 2 && v > stromscore::kRissStart)   // ab 80 % reisst die Unruhe: dieser Teil des Balkens ist rot
            {
                juce::Graphics::ScopedSaveState save (g);
                g.reduceClipRegion (juce::Rectangle<float> (bar.getX() + bar.getWidth() * stromscore::kRissStart, bar.getY(), bar.getWidth(), bar.getHeight()).toNearestInt());
                g.setColour (juce::Colour (0xffe04848));
                g.fillRoundedRectangle (filled, 3.0f);
            }
            const juce::Point<float> knob (bar.getX() + bar.getWidth() * v, bar.getCentreY());
            g.setColour (accent);
            g.fillEllipse (juce::Rectangle<float> (11.0f, 11.0f).withCentre (knob));
            g.setColour (panel);
            g.drawEllipse (juce::Rectangle<float> (11.0f, 11.0f).withCentre (knob), 1.5f);
            g.setColour (text);
            g.drawText (juce::String (juce::roundToInt (v * 100.0f)) + " %", juce::Rectangle<float> ((float) w - 14.0f - kBarValueW, yy, kBarValueW, 16.0f),
                        juce::Justification::centredRight);
        }
    }

    // Akkorde der Wendung als Chips
    if (playing && numChips > 0)
    {
        const float gap = 6.0f;
        const float cw = ((float) w - 28.0f - gap * 3.0f) / 4.0f;
        for (int i = 0; i < numChips; ++i)
        {
            const juce::Rectangle<float> c (14.0f + (float) (i % 4) * (cw + gap), 76.0f + (float) (i / 4) * 28.0f, cw, 24.0f);
            const bool on = i == current;
            g.setColour (on ? accent : line);
            if (on) g.fillRoundedRectangle (c, 5.0f); else g.drawRoundedRectangle (c.reduced (0.5f), 5.0f, 1.0f);
            g.setColour (on ? juce::Colours::black : text);
            g.setFont (juce::FontOptions (12.0f, juce::Font::bold));
            g.drawFittedText (chips[i], c.toNearestInt().reduced (2, 0), juce::Justification::centred, 1, 0.8f);
        }
    }
}

// ---------------------------------------------------------------- Ebene

void LayerView::paint (juce::Graphics& g)
{
    auto r = getLocalBounds().toFloat();
    g.setColour (panel);
    g.fillRoundedRectangle (r, 8.0f);
    g.setColour (line);
    g.drawRoundedRectangle (r.reduced (0.5f), 8.0f, 1.0f);

    g.setColour (active ? accent : dim);
    g.setFont (juce::FontOptions (12.0f, juce::Font::bold));
    g.drawFittedText (title, 12, 8, (int) r.getWidth() - 100, 16, juce::Justification::centredLeft, 1, 0.75f);

    // Lampe(n) rechts neben Solo: ein Punkt je Ausgang
    for (int i = 0; i < numLamps; ++i)
    {
        const float d = numLamps == 1 ? 12.0f : 9.0f;
        const juce::Rectangle<float> lamp (numLamps == 1 ? r.getWidth() - 26.0f : r.getWidth() - 31.0f + (float) i * 11.0f, 16.0f - d * 0.5f, d, d);
        g.setColour (line);
        g.fillEllipse (lamp);
        if (activity[i] > 0.02f)
        {
            g.setColour (accent.withAlpha (juce::jlimit (0.0f, 1.0f, activity[i])));
            g.fillEllipse (lamp);
        }
    }

    g.setColour (active ? text : dim);
    g.setFont (juce::FontOptions (11.5f));
    for (int i = 0; i < 4; ++i)
        if (rowLabel[i].isNotEmpty())
            g.drawFittedText (rowLabel[i], 12, 34 + i * 28, kLabelW, 24, juce::Justification::centredLeft, 1, 0.8f);
}

// ---------------------------------------------------------------- Tonumfang

RangePanel::RangePanel (StromscoreProcessor& p, int rangeIndex, juce::Colour panel, juce::Colour accent, juce::Colour text, juce::Colour dim)
    : processor (p), layer (rangeIndex), panelColour (panel), accentColour (accent), textColour (text), dimColour (dim)
{
    const juce::String n (layer + 1);
    onButton.setClickingTogglesState (true);
    onButton.setButtonText (u8 ("Tonumfang begrenzen"));
    onButton.setTooltip (u8 ("Aus: die Ebene spielt in jeder Lage (für Synths). Ein: alle Töne bleiben im eingestellten Bereich."));
    onAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ButtonAttachment> (processor.apvts, "umfang" + n, onButton);
    addAndMakeVisible (onButton);

    templateBox.setTextWhenNothingSelected (u8 ("Vorlage für ein Instrument …"));
    int id = 1;
    for (const auto& t : StromscoreProcessor::rangeTemplates())
        templateBox.addItem (juce::String (juce::CharPointer_UTF8 (t.name)) + "   " + StromscoreProcessor::noteName (t.lo) + u8 ("–") + StromscoreProcessor::noteName (t.hi), id++);
    templateBox.onChange = [this]
    {
        const int i = templateBox.getSelectedId() - 1;
        const auto& list = StromscoreProcessor::rangeTemplates();
        if (i >= 0 && i < (int) list.size()) applyRange (list[(size_t) i].lo, list[(size_t) i].hi);
    };
    templateBox.setTooltip (u8 ("Übliche Tonumfänge als Richtwert. Genauer: „Anlernen“ mit dem eigenen Patch."));
    addAndMakeVisible (templateBox);

    for (int note = 0; note < 128; ++note)
    {
        const auto label = StromscoreProcessor::noteName (note) + "  (" + juce::String (note) + ")";
        loBox.addItem (label, note + 1);
        hiBox.addItem (label, note + 1);
        toneBox.addItem (label, note + 1);
    }
    loAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ComboBoxAttachment> (processor.apvts, "tief" + n, loBox);
    hiAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ComboBoxAttachment> (processor.apvts, "hoch" + n, hiBox);
    loBox.setTooltip (u8 ("Tiefster Ton, den das Instrument spielen kann (mittleres C = C3)."));
    hiBox.setTooltip (u8 ("Höchster Ton, den das Instrument spielen kann (mittleres C = C3)."));
    addAndMakeVisible (loBox);
    addAndMakeVisible (hiBox);

    learnButton.setButtonText ("Anlernen");
    learnButton.setTooltip (u8 ("Danach die tiefste und die höchste spielbare Taste des Instruments auf dem Keyboard drücken (die Reihenfolge ist egal). Das Keyboard muss auf die Spur mit Stromscore geleitet sein. Mit „Keyboard durchleiten“ hörst du dabei dein Instrument."));
    learnButton.onClick = [this]
    {
        if (processor.learnLayer.load() == layer)
        {
            processor.learnLayer.store (-1);
            status = {};
        }
        else
        {
            processor.learnFirst.store (-1); processor.learnSecond.store (-1);
            processor.learnLayer.store (layer);
            status = u8 ("Tiefste und höchste spielbare Taste drücken …");
        }
        repaint();
    };
    addAndMakeVisible (learnButton);

    // Durchleiten: nur solange dieses Fenster offen ist
    thruButton.setClickingTogglesState (true);
    thruButton.setButtonText ("Keyboard durchleiten");
    thruButton.setToggleState (processor.thruWanted.load(), juce::dontSendNotification);
    thruButton.setTooltip (u8 ("Solange dieses Fenster offen ist, gehen die Tasten deines Keyboards auf den MIDI-Kanal dieser Ebene. So hörst du dein eigenes Instrument und findest den spielbaren Bereich oder die Taste des Samples. Beim Schließen des Fensters hört das Durchleiten auf, und alle gehaltenen Töne enden."));
    thruButton.onClick = [this] { processor.thruWanted.store (thruButton.getToggleState()); updateThru(); };
    addAndMakeVisible (thruButton);

    if (isStich())
    {
        modeFixed.setButtonText ("Fest");
        modeChord.setButtonText ("Akkord");
        modeFixed.setTooltip (u8 ("Fest: Der Stich spielt immer dieselbe Taste, unabhängig von Akkord, Oktave und Tonumfang. Für ein perkussives Sample, etwa Pauke oder große Trommel, das in deiner Library auf genau einer Taste liegt."));
        modeChord.setTooltip (u8 ("Akkord: Der Stich spielt den Grundton des aktuellen Akkords, ein einzelner Ton in tiefer Mittellage. Für Klavier, Synth-Stab oder Pizzicato-Bass."));
        for (auto* b : { &modeFixed, &modeChord }) { b->setRadioGroupId (91); addAndMakeVisible (b); }
        modeAttachment = std::make_unique<juce::ParameterAttachment> (*processor.apvts.getParameter ("stichModus"),
            [this] (float v)
            {
                const bool fixed = juce::roundToInt (v) == 0;
                modeFixed.setToggleState (fixed, juce::dontSendNotification);
                modeChord.setToggleState (! fixed, juce::dontSendNotification);
                updateMode (fixed);
            }, nullptr);
        modeFixed.onClick = [this] { modeAttachment->setValueAsCompleteGesture (0.0f); };
        modeChord.onClick = [this] { modeAttachment->setValueAsCompleteGesture (1.0f); };

        toneAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ComboBoxAttachment> (processor.apvts, "stichTon", toneBox);
        toneBox.setTooltip (u8 ("Die Taste, auf der das Sample liegt (mittleres C = C3)."));
        addAndMakeVisible (toneBox);
        tonePlay.setButtonText (u8 ("Hören"));
        tonePlay.setTooltip (u8 ("Schlägt die Taste einmal auf dem Kanal des Stichs an."));
        tonePlay.onClick = [this]
        {
            processor.audition (juce::roundToInt (processor.apvts.getRawParameterValue ("stichTon")->load()), processor.channelMaskForRange (5));
        };
        addAndMakeVisible (tonePlay);
        toneLearn.setButtonText ("Taste anlernen");
        toneLearn.setTooltip (u8 ("Danach die Taste auf dem Keyboard drücken, auf der das Sample liegt. Mit „Keyboard durchleiten“ hörst du dabei dein Instrument und kannst erst suchen."));
        toneLearn.onClick = [this]
        {
            if (processor.learnTone.load()) { processor.learnTone.store (false); status = {}; }
            else
            {
                processor.learnToneNote.store (-1);
                processor.learnTone.store (true);
                status = u8 ("Die Taste des Samples drücken …");
            }
            repaint();
        };
        addAndMakeVisible (toneLearn);
        modeAttachment->sendInitialUpdate();
    }
    if (! isStich()) updateMode (false);
    updateThru();
    startTimerHz (15);
}

RangePanel::~RangePanel()
{
    if (processor.learnLayer.load() == layer) processor.learnLayer.store (-1);
    processor.learnTone.store (false);
    processor.thruMask.store (0);   // Fenster zu: Durchleiten aus, gehaltene Toene enden im naechsten Block
}

bool RangePanel::fixedMode() const
{
    return isStich() && shownFixed;   // der Wert kommt aus dem Klick selbst, nicht aus dem (noch alten) Parameter
}

void RangePanel::updateMode (bool fixed)
{
    shownFixed = isStich() && fixed;
    fixed = shownFixed;
    for (auto* c : std::initializer_list<juce::Component*> { &onButton, &templateBox, &loBox, &hiBox, &learnButton }) c->setVisible (! fixed);
    for (auto* c : std::initializer_list<juce::Component*> { &toneBox, &tonePlay, &toneLearn }) c->setVisible (fixed);
    if (! fixed && processor.learnTone.load()) { processor.learnTone.store (false); status = {}; }
    if (fixed && processor.learnLayer.load() == layer) { processor.learnLayer.store (-1); status = {}; }
    setSize (300, fixed ? 226 : 246 + offset());
    resized();
    repaint();
}

void RangePanel::updateThru()
{
    processor.thruMask.store (thruButton.getToggleState() ? processor.channelMaskForRange (layer) : 0);
}

void RangePanel::setParam (const juce::String& id, float v)
{
    if (auto* prm = processor.apvts.getParameter (id))
    {
        prm->beginChangeGesture();
        prm->setValueNotifyingHost (prm->convertTo0to1 (v));
        prm->endChangeGesture();
    }
}

void RangePanel::applyRange (int lo, int hi)
{
    const juce::String n (layer + 1);
    if (lo > hi) std::swap (lo, hi);
    setParam ("tief" + n, (float) lo);
    setParam ("hoch" + n, (float) hi);
    setParam ("umfang" + n, 1.0f);
    repaint();
}

void RangePanel::timerCallback()
{
    updateThru();   // falls der Kanal der Ebene inzwischen gewechselt hat
    if (isStich())
    {
        toneLearn.setToggleState (processor.learnTone.load(), juce::dontSendNotification);
        const int t = processor.learnToneNote.load();
        if (processor.learnTone.load() && t >= 0)
        {
            processor.learnTone.store (false);
            setParam ("stichTon", (float) t);
            status = u8 ("Angelernt: ") + StromscoreProcessor::noteName (t);
            repaint();
        }
    }
    if (processor.learnLayer.load() != layer) { learnButton.setToggleState (false, juce::dontSendNotification); return; }
    learnButton.setToggleState (true, juce::dontSendNotification);
    const int a = processor.learnFirst.load(), b = processor.learnSecond.load();
    if (a >= 0 && b >= 0)
    {
        processor.learnLayer.store (-1);
        applyRange (a, b);
        status = u8 ("Angelernt: ") + StromscoreProcessor::noteName (std::min (a, b)) + u8 (" bis ") + StromscoreProcessor::noteName (std::max (a, b));
        repaint();
    }
    else if (a >= 0)
    {
        const auto t = StromscoreProcessor::noteName (a) + u8 (" gemerkt, jetzt die zweite Taste …");
        if (status != t) { status = t; repaint(); }
    }
}

void RangePanel::paint (juce::Graphics& g)
{
    g.fillAll (panelColour);
    g.setColour (accentColour);
    g.setFont (juce::FontOptions (12.0f, juce::Font::bold));
    g.drawText ((isStich() ? u8 ("STICH · TON UND UMFANG") : u8 ("TONUMFANG · ") + StromscoreProcessor::rangeName (layer).toUpperCase()),
                10, 6, getWidth() - 20, 16, juce::Justification::centredLeft);
    g.setColour (dimColour);
    g.setFont (juce::FontOptions (11.0f));
    juce::String hint = status;
    int hintY = 0;
    if (fixedMode())
    {
        g.drawText (u8 ("Taste des Samples"), 10, 64, 200, 14, juce::Justification::centredLeft);
        if (hint.isEmpty()) hint = u8 ("Der Stich spielt immer diese Taste, unabhängig von Akkord, Oktave und Tonumfang.");
        hintY = 186;
    }
    else
    {
        const int o = offset();
        g.drawText (u8 ("Tiefster Ton"), 10, 88 + o, 120, 14, juce::Justification::centredLeft);
        g.drawText (u8 ("Höchster Ton"), 155, 88 + o, 120, 14, juce::Justification::centredLeft);
        const juce::String n (layer + 1);
        const int lo = juce::roundToInt (processor.apvts.getRawParameterValue ("tief" + n)->load());
        const int hi = juce::roundToInt (processor.apvts.getRawParameterValue ("hoch" + n)->load());
        if (hint.isEmpty())
            hint = std::abs (hi - lo) < 12 ? u8 ("Enger als eine Oktave: Töne, die nicht hineinpassen, werden durch Akkordtöne im Bereich ersetzt.")
                                           : u8 ("Töne außerhalb wandern um ganze Oktaven nach innen. Kein Ton fällt weg.");
        hintY = 204 + o;
    }
    g.setColour (status.isNotEmpty() ? accentColour : dimColour);
    g.drawFittedText (hint, 10, hintY, getWidth() - 20, 34, juce::Justification::topLeft, 2, 0.9f);
}

void RangePanel::resized()
{
    const int w = getWidth();
    if (isStich())
    {
        modeFixed.setBounds (10, 28, (w - 26) / 2, 24);
        modeChord.setBounds (16 + (w - 26) / 2, 28, w - 26 - (w - 26) / 2, 24);
    }
    if (fixedMode())
    {
        toneBox.setBounds (10, 82, w - 20 - 84, 26);
        tonePlay.setBounds (w - 10 - 78, 82, 78, 26);
        toneLearn.setBounds (10, 116, w - 20, 26);
        thruButton.setBounds (10, 150, w - 20, 26);
        return;
    }
    const int o = offset();
    onButton.setBounds (10, 28 + o, w - 20, 24);
    templateBox.setBounds (10, 58 + o, w - 20, 24);
    loBox.setBounds (10, 104 + o, 135, 24);
    hiBox.setBounds (155, 104 + o, w - 165, 24);
    learnButton.setBounds (10, 138 + o, w - 20, 26);
    thruButton.setBounds (10, 170 + o, w - 20, 26);
}

// ---------------------------------------------------------------- Eigene Akkordfolge

void SlotPanel::paint (juce::Graphics& g)
{
    auto r = getLocalBounds().toFloat();
    g.setColour (panel);
    g.fillRoundedRectangle (r, 8.0f);
    g.setColour (accent);
    g.drawRoundedRectangle (r.reduced (0.5f), 8.0f, 1.5f);

    g.setColour (accent);
    g.setFont (juce::FontOptions (13.0f, juce::Font::bold));
    g.drawText (u8 ("EIGENE AKKORDFOLGE"), 16, 12, 300, 18, juce::Justification::centredLeft);
    g.setColour (dim);
    g.setFont (juce::FontOptions (12.0f));
    g.drawText (u8 ("Bis zu acht Akkorde mit Grundton, Art und Länge. Plätze mit „–“ werden übersprungen, danach beginnt die Folge von vorn."),
                16, 32, getWidth() - 32, 18, juce::Justification::centredLeft);
    const int cw = (getWidth() - 32 - 7 * 8) / stromscore::kMaxChords;
    g.setFont (juce::FontOptions (11.0f, juce::Font::bold));
    for (int i = 0; i < stromscore::kMaxChords; ++i)
        g.drawText (juce::String (i + 1), 16 + i * (cw + 8), 66, cw, 16, juce::Justification::centred);
    g.setColour (text);
    g.setFont (juce::FontOptions (12.0f));
    g.drawText (totalText, 16, getHeight() - 42, getWidth() - 170, 28, juce::Justification::centredLeft);
}

// ---------------------------------------------------------------- Farben

StromscoreEditor::Theme StromscoreEditor::darkTheme()
{
    return { juce::Colour (0xff182326), juce::Colour (0xff233539), juce::Colour (0xfff5781a),
             juce::Colour (0xffe8ecec), juce::Colour (0xff8fa1a5), juce::Colour (0xff35494e), true };
}
StromscoreEditor::Theme StromscoreEditor::lightTheme()
{
    return { juce::Colour (0xffd5dbda), juce::Colour (0xffe8eae9), juce::Colour (0xfff5781a),
             juce::Colour (0xff233539), juce::Colour (0xff5d6e72), juce::Colour (0xffb5bfbe), false };
}

// ---------------------------------------------------------------- Hilfe

// Compact channel settings; all outputs on one channel share the same physical CC stream.
class CcRangePanel final : public juce::Component
{
public:
    CcRangePanel (StromscoreProcessor& p, int initial) : processor (p)
    {
        setSize (500, 286);
        addAndMakeVisible (channel); for (int ch = 1; ch <= 16; ++ch) channel.addItem (p.ccChannelDescription (ch), ch);
        addAndMakeVisible (enabled); enabled.setButtonText (u8 ("CC-Ausgabe für alle Kanäle"));
        enabled.setClickingTogglesState (true);
        enabledAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ButtonAttachment> (p.apvts, "dynamikCc", enabled);
        addAndMakeVisible (hint); hint.setText (u8 ("Bereiche gelten gemeinsam für alle Ausgänge auf diesem Kanal. Ausdruck blendet bei weichem Aufbau/Ende bis 0 aus. Die CC-Zuordnung muss zu deinem Instrument passen."), juce::dontSendNotification);
        hint.setJustificationType (juce::Justification::topLeft); hint.setFont (juce::FontOptions (12.0f));
        for (int i = 0; i < 4; ++i)
        {
            addAndMakeVisible (labels[i]); addAndMakeVisible (values[i]);
            labels[i].setText (i == 0 ? "Dynamik von" : i == 1 ? "bis" : i == 2 ? "Ausdruck von" : "bis", juce::dontSendNotification);
            values[i].setSliderStyle (juce::Slider::LinearHorizontal); values[i].setTextBoxStyle (juce::Slider::TextBoxRight, false, 44, 24);
            values[i].setRange (0, 127, 1);
        }
        channel.onChange = [this] { attach(); };
        channel.setSelectedId (juce::jlimit (1, 16, initial), juce::dontSendNotification); attach();
    }
    void paint (juce::Graphics& g) override { g.fillAll (getLookAndFeel().findColour (juce::PopupMenu::backgroundColourId)); }
    void resized() override
    {
        channel.setBounds (14, 12, 472, 26); enabled.setBounds (14, 46, 472, 24);
        for (int i = 0; i < 4; ++i) { labels[i].setBounds (14, 78 + i * 30, 96, 26); values[i].setBounds (110, 78 + i * 30, 376, 26); }
        hint.setBounds (14, 204, 472, 74);
    }
private:
    void attach()
    {
        for (auto& a : attachments) a.reset();
        for (int i = 0; i < 4; ++i)
            attachments[i] = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment> (processor.apvts,
                "cc" + juce::String (i / 2) + (i % 2 == 0 ? "Lo" : "Hi") + juce::String (channel.getSelectedId()), values[i]);
    }
    StromscoreProcessor& processor;
    juce::ComboBox channel;
    juce::TextButton enabled;
    juce::Label labels[4], hint;
    juce::Slider values[4];
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> attachments[4];
    std::unique_ptr<juce::AudioProcessorValueTreeState::ButtonAttachment> enabledAttachment;
};

#include "WendungInfo.h"
class WendungInfoPanel final : public juce::Component
{
public:
    WendungInfoPanel (int genre, int selected, int key) : tonic (key)
    {
        setSize (650, 410); addAndMakeVisible (choices); addAndMakeVisible (details);
        details.setMultiLine (true); details.setReadOnly (true); details.setScrollbarsShown (true); details.setCaretVisible (false);
        details.setFont (juce::FontOptions (14.0f));
        for (int g = 0; g < 2; ++g)
            for (int i = 0; i < stromscore::wendungCount (g); ++i)
                choices.addItem (u8 (g == 0 ? "Score · " : "Pop-Rock · ") + u8 (stromscore::wendungAt (g, i).name), 1 + g * 100 + i);
        choices.onChange = [this] { update(); };
        choices.setSelectedId (1 + genre * 100 + juce::jlimit (0, stromscore::wendungCount (genre) - 1, selected), juce::dontSendNotification);
        update();
    }
    void paint (juce::Graphics& g) override { g.fillAll (getLookAndFeel().findColour (juce::PopupMenu::backgroundColourId)); }
    void resized() override { choices.setBounds (14, 12, getWidth() - 28, 28); details.setBounds (14, 50, getWidth() - 28, getHeight() - 64); }
private:
    void update()
    {
        const int id = choices.getSelectedId() - 1, genre = id / 100, index = id % 100;
        const auto& w = stromscore::wendungAt (genre, index);
        const auto& info = genre == 0 ? kScoreInfo[index] : kPopInfo[index];
        juce::String t = u8 (w.name) + "\n\nHarmonik (aktuelle Tonart):\n";
        char chord[96];
        for (int c = 0; c < w.n; ++c)
        {
            stromscore::chordName (tonic, w.ch[c].root, w.ch[c].type, chord, 96);
            t << (c > 0 ? " → " : "") << u8 (chord);
            if (w.ch[c].bass >= 0) t << " / Bass " << StromscoreProcessor::keyNames()[(tonic + w.ch[c].bass) % 12];
            t << " (" << w.ch[c].bars << (w.ch[c].bars == 1 ? " Takt)" : " Takte)");
        }
        t << "\n\nIdee und Bezug:\n" << u8 (info.idea) << "\n\nInstrumentierung:\n" << u8 (info.instruments);
        t << "\n\nAuto-Muster:\nFläche: " << StromscoreProcessor::padPatternNames()[w.pad]
          << "; Bass: " << StromscoreProcessor::bassPatternNames()[w.bass[0]] << " / " << StromscoreProcessor::bassPatternNames()[w.bass[1]]
          << "; Arp: " << StromscoreProcessor::arpFigureNames()[w.arp[0]] << " / " << StromscoreProcessor::arpFigureNames()[w.arp[1]];
        t << "\n\nQuelle / Einordnung:\n" << u8 (info.source);
        t << "\n\nEigene regelbasierte Wendung, keine Transkription eines bestimmten Titels. Instrumente und Artikulationen kommen aus deinen eigenen Patches. Taktart und Tempo folgen deiner Auswahl bzw. dem Projekt; Walzer bitte in 3/4 einrichten. Leise Intensität erhält die Akkordfarben; Tonumfang und Mute/Solo können die tatsächlich spielbare Besetzung begrenzen.";
        details.setText (t, false);
    }
    int tonic;
    juce::ComboBox choices;
    juce::TextEditor details;
};

static juce::AttributedString buildHelp (juce::Colour text, juce::Colour accent, juce::Colour dim)
{
    juce::AttributedString s;
    s.setWordWrap (juce::AttributedString::byWord);
    s.setJustification (juce::Justification::topLeft);

    auto head = [&] (const char* t) { s.append (u8 (t) + "\n", juce::Font (juce::FontOptions (14.0f, juce::Font::bold)), accent); };
    auto body = [&] (const char* t) { s.append (u8 (t) + "\n\n", juce::Font (juce::FontOptions (13.0f)), text); };
    auto bold = [&] (const char* t) { s.append (u8 (t), juce::Font (juce::FontOptions (13.0f, juce::Font::bold)), text); };
    auto note = [&] (const char* t) { s.append (u8 (t) + "\n\n", juce::Font (juce::FontOptions (12.0f)), dim); };

    s.append (u8 ("Hilfe · v") + juce::String (PLUGIN_VERSION_TEXT) + "\n\n", juce::Font (juce::FontOptions (17.0f, juce::Font::bold)), accent);

    head ("Was das Plugin macht");
    body ("Es erzeugt Musik für Untermalung in fünf Ebenen und gibt sie als MIDI aus: Fläche, Bass, Arp, Akzent und Gegenstimme, auf bis zu acht frei wählbaren MIDI-Kanälen. Die Ebenen sind für tongebende Instrumente gedacht; nur der Stich kann auf Wunsch fest auf einer Taste ein perkussives Sample spielen, etwa eine Pauke. Die Klänge kommen aus deinen eigenen Instrumenten. Die Noten sind als Ausgangspunkt gedacht, den du weiter bearbeitest. Es läuft im Takt des Projekts: Wiedergabe starten, springen oder loopen, und es spielt an der richtigen Stelle weiter. Mit dem Start der Wiedergabe beginnt eine Szene mit Einstieg, Aufbau und auf Wunsch einem Ende. Gleicher Szenenstart, Wurf, Einstellungen und Steuerungsverlauf ergeben dieselben Noten. Für eine feste Fassung die MIDI-Ausgabe aufnehmen.");

    head ("Woher die Musik kommt");
    bold ("Es verwendet keine KI. ");
    body ("STROMSCORE arbeitet mit festen Regeln, nicht mit trainierten Modellen und nicht mit fremdem Material. Die Grundlage ist der Stil, den Lars Eickstädt über Jahre für seine Hörspiele entwickelt hat, geprägt von großen Filmkomponisten und der Musik klassischer Hörspiele. Daraus ist ein Vorrat an Wendungen entstanden: Akkordfolgen, Figuren und Rhythmen. Je nach Stimmung zieht das Plugin daraus. Melodien bekannter Stücke werden nicht nachgebaut.");

    head ("Neu: Wendungsinfo und CC-Bereiche");
    body ("WENDUNGSINFO neben der Akkordanzeige erklärt jede der 48 Score- und 36 Pop-Rock-Wendungen: Akkorde in deiner Tonart, Muster, Instrumentierung und stilistische Bezüge. Die neun neuen Album-Pop-, Gitarren- und Studio-Pop-Wendungen haben eigene rhythmische Gegenstimmen; es werden keine bekannten Melodien kopiert.");
    body ("Oben im Menü MIDI / CC unter „Ausgang: CC-Bereiche …“ stehen die Dynamik- und Ausdrucksbereiche je MIDI-Kanal. Die Kanalnamen zeigen alle zugeordneten Ausgänge, auch Fläche kurz und Akzent Stich. „CC-Ausgabe für alle Kanäle“ schaltet die gesamte Ausgabe ein; die Bereiche gelten jeweils nur für den gewählten Kanal. Beispiel: Dynamik von 100 bis 127, Ausdruck von 60 bis 127. Die ganze Kurve wird relativ in diesen Bereich übersetzt; gleiche Grenzen ergeben einen festen Wert. Geteilte Kanäle teilen immer denselben Bereich und dieselben Controller. Bei vertauschten Grenzen zählt der kleinere Wert als Minimum. Die Grundeinstellung neuer Bereiche ist 60–127. Die Ausgabe bleibt zunächst aus und wird im CC-Menü oder im Bereichsfenster eingeschaltet.");
    body ("Dynamik (normal CC1) wählt bei vielen Orchesterbibliotheken die Klangstärke, Ausdruck (normal CC11) regelt die Lautstärke. Das ist patchabhängig: CC1 kann auch Vibrato oder Modulation sein. Prüfe die Zuordnung in deinem Instrument. Weiche Ein-/Ausblendungen laufen über Ausdruck bis 0, bewusst auch unterhalb des eingestellten Arbeitsbereichs. Hohe Dynamikbereiche bleiben davon unberührt. Ohne passenden Ausdrucks-CC kann eine bereits gehaltene Note nicht weich einblenden; Velocity allein wirkt nur beim Anschlag.");
    body ("Bei geringer Intensität bleiben Septimen, Nonen und andere Akkordfarben vollständig erhalten, auch beim schüchternen Flächeneinstieg. Er wird über Lautstärke und Einsatz weich, nicht durch das Weglassen der Harmonik. Enge Tonumfänge können mehrere Akkordtöne auf dieselbe Note falten. Für alle Farben mindestens eine Oktave, bei komplexen Akkorden besser mehr zulassen.");
    body ("MIDI-Export beginnt eine neue Szene ab Takt 1 mit den aktuellen Einstellungen. Frühere oder zukünftige DAW-Automation wird nicht rekonstruiert. Endet die gewählte Länge genau am harten Szenenende, enthält die Datei zusätzlich den Schlussakkord und seinen kurzen Ausklang (eine Viertelnote Reserve). Der klingende Schluss wird nicht mehr abgeschnitten.");

    head ("Einrichten in Studio One");
    body ("1. Lege eine Instrumentenspur mit Stromscore an. 2. Lege für jede Ebene, die du hören willst, eine Instrumentenspur mit deinem Instrument an. 3. Stelle bei jeder dieser Spuren als Eingang Stromscore ein und wähle den MIDI-Kanal. Vorgabe: Fläche lang 1, Fläche kurz 2, Bass lang 3, Bass kurz 4, Arp 5, Akzent Tupfer 6, Akzent Stich 7, Gegenstimme 8. Die Kanäle stellst du in jedem Ebenen-Kasten selbst ein. 4. Schalte die Spuren auf Monitor. Zum Weiterarbeiten nimmst du die Ausgabe einfach auf diesen Spuren auf.");
    note ("Ohne eigene Instrumente hörst du mit VORHÖREN einen einfachen Testklang direkt aus dem Plugin.");

    head ("Das Stimmungsfeld");
    body ("Ziehe den Punkt durch das Feld. Waagerecht ist die FÄRBUNG: links dunkel (Bedrohung, Trauer, Lauern), rechts hell (Wärme, Staunen, Triumph). Senkrecht ist die INTENSITÄT: unten ruhig und dünn, oben aufgewühlt und dicht. Unten in der Mitte liegt RUHE, der neutrale Ausgangspunkt. Färbung, Intensität und Unruhe stehen rechts in der Akkord-Anzeige laufend in Prozent.");
    body ("Mit dem Mausrad über dem Feld (oder per Controller) änderst du die dritte Achse, die UNRUHE. Sie zeigt sich als Ring um den Punkt: Je größer und zittriger, desto mehr Reibung, Dissonanz, Halbtöne und verschobene Betonungen. Ab mittlerer Unruhe vibriert ein zweiter, äußerer Ring. Bei wenig Intensität sind es einzelne fremde Töne, bei viel Intensität kratzt der ganze Satz.");
    body ("Ab 80 % Unruhe kommt der RISS dazu, wie die kreischenden Streicher in Herrmanns „Psycho“: kurze, harte Stöße aus zwei Tönen im Halbtonabstand hoch über dem Satz, auf dem Kanal der kurzen Fläche. Dort liegen am besten Staccato- oder Spiccato-Streicher. Bei 80 % kommt er selten und leiser, bis 100 % immer häufiger, lauter und doppelt, ganz oben mit einem dritten Reibungston. Er hängt nur an der Unruhe, so kann auch eine leise Szene einmal wehtun. Im Feld flackert der äußere Ring dann rot. Ist die Fläche stumm, schweigt auch der Riss.");
    body ("RUHEZONE: Ganz unten im Feld (Intensität unter etwa 10 %) bleibt der Akkord stehen, über die ganze untere Kante. Die Unruhe wirkt dort weiter, nur der Akkord wechselt nicht, bis du nach oben gehst. Die Balken für Färbung, Intensität und Unruhe in der Akkord-Anzeige lassen sich ebenfalls ziehen, der Punkt im Feld folgt. Ab 80 % Unruhe, wo der Riss beginnt, wird der Unruhe-Ring um den Punkt rot und zappelt wilder; auch der Balken ist ab dort rot.");
    body ("Alle drei Achsen lassen sich automatisieren. So fährst du durch eine Szene: langsam vom Lauern in die Panik und am Ende in die Erlösung.");

    head ("Szene: Einstieg, Aufbau und Ende");
    body ("Eine Szene beginnt mit dem Start der Wiedergabe. Springst du während der Wiedergabe nach vorn oder läuft ein Loop, der nicht vor den Start zurückspringt, geht dieselbe Szene weiter. Stoppen und neu starten beginnt eine neue Szene, ebenso ein Sprung vor den Start. Die herausgezogene MIDI-Datei beginnt immer mit einer Szene.");
    body ("Mit AUFBAU spielt am Anfang nur die Ebene des EINSTIEGS. Die anderen folgen nacheinander auf Taktgrenzen, bis nach 4, 8 oder 16 Takten alles da ist; dabei wird die Musik von dünn zu dicht. Einstiege: Fläche, schüchtern (ein leiser, vollständig gefärbter Akkord), Bass-Schlag (ein tiefer Ton, kräftig gesetzt), Puls (kurze Viertel auf dem Grundton, wie ein Ticken, den ganzen Aufbau lang), Arpeggio, Akzent (ein Stich oder Tupfer in der Stille), Gegenstimme oder alles zugleich. Danach kommen die verwandten Ebenen: Beginnt der Bass, folgt das Arpeggio, dann die Fläche, zuletzt Akzent und Gegenstimme. Gewählt hat immer Vorrang. Auf AUTO würfelt Stromscore den Einstieg, passend zu Genre und Stimmung und nur aus Ebenen, die gerade spielen können. NEU WÜRFELN ergibt einen anderen Einstieg und ein anderes Motiv; derselbe Wurf ergibt immer dasselbe. Die Ebene des Einstiegs spielt im Aufbau auch dann, wenn die Intensität für sie eigentlich zu niedrig ist; danach gelten wieder die normalen Schwellen. Aus: alle Ebenen setzen gleich ein, wie vor Version 1.3.");
    body ("HÄRTE bestimmt, wie eine Ebene einsetzt: unter 50 % weich eingeblendet (ganz links über zwei Takte), über 50 % mit einem kräftigen ersten Anschlag. Das gilt im Aufbau und immer, wenn eine Ebene mit steigender Intensität dazukommt. Ist die Dynamik per CC eingeschaltet, folgt sie mit.");
    body ("Mit LÄNGE endet die Szene nach 8 bis 64 Takten. ENDE wählt, wie: HART spielt bis zum Schluss mit allen Ebenen; im letzten Takt zieht sich der Bass zurück und ein Stich kündigt an, dann kommt ein kurzer, kräftiger Schlag auf dem Grundakkord und danach Stille. AUSKLINGEND lässt die Ebenen nacheinander gehen, was zuletzt kam, zuerst, und die Ebene des Einstiegs klingt bis zum Ende. OFFEN wird zum Schluss noch dichter und bricht dann ohne Schlussschlag ab, die Spannung bleibt stehen. Unbegrenzt: Die Musik läuft weiter.");
    note ("Rechts in der Leiste FAHRT steht während der Wiedergabe der Stand der Szene: Takt, Einstieg, Aufbau, Fahrt und wie viele Takte bis zum Ende bleiben.");

    head ("Fahrt von A nach B");
    body ("Mit FAHRT wandert die Musik selbst vom Punkt im Feld (A) zu einem Ziel (B). B erscheint als Ring im Stimmungsfeld; Links setzt und zieht immer A, rechts immer B. Eine linke Geste oder ein Zug an Färbung/Intensität übernimmt sofort manuell und beendet die Fahrt. Das Mausrad steuert nur Unruhe. B bleibt auch bei ausgeschalteter Fahrt und nach dem Wiederöffnen des Projekts sichtbar; liegen A und B zusammen, steht dort A/B. Mit der rechten Maustaste setzt du das Ziel B, ohne dass die Fahrt startet: Der Ring erscheint dort, die Musik bleibt bei A, und mit FAHRT geht es los. Während der Hinfahrt lässt sich B rechts ändern: Die aktuelle Position bleibt erhalten, der restliche Weg wird auf die verbleibende Dauer verteilt. Auf der Rückfahrt bleibt das ursprüngliche A das Ziel; ein geändertes B gilt für die nächste Fahrt. Ein DAW-Sprung rekonstruiert die Kurve aus den aktuellen Einstellungen, ohne vorherige manuelle Zieländerungen. Solche Änderungen für wiederholbare Exporte als DAW-Automation aufnehmen. START legt fest, wann die Fahrt beginnt (sofort oder ab Takt 5, 9, 17, 33), DAUER, wie lange sie braucht, KURVE den Verlauf: gleichmäßig, erst langsam und dann schnell, in vier Stufen oder hin und zurück (zur Mitte der Dauer bei B, am Ende wieder bei A). Kommt die Fahrt bei B an, wird B zum neuen A, und die Fahrt schaltet sich aus: Du bleibst dort und kannst von Hand weiterziehen. Schaltest du sie unterwegs aus, wird die Stelle, an der die Musik gerade ist, zu A; nichts springt zurück. Schaltest du FAHRT während der Wiedergabe wieder ein, geht es mit dem nächsten Takt vom Punkt aus los. START gilt nur, wenn die Wiedergabe mit eingeschalteter Fahrt beginnt. Während der Wiedergabe zeigt ein kleiner Punkt, wo die Musik gerade ist; der Unruhe-Ring und die Werte in der Akkord-Anzeige wandern mit ihm.");
    body ("Weil Stromscore das Ziel kennt, bereitet es eine Fahrt nach oben vor: Im Takt vor dem Ziel zieht sich der Bass in der zweiten Hälfte zurück und ein Stich kündigt an, am Ziel setzen Fläche und Bass kräftig neu ein. Von Hand fahren und Automation gehen weiterhin; die Fahrt geht dann vom aktuellen Punkt A aus.");

    head ("Trägheit");
    body ("Damit eine Ebene nicht an- und ausgeht, wenn der Punkt an ihrer Schwelle wackelt, schalten die Ebenen nur auf Taktanfängen. Eine Ebene geht erst wieder aus, wenn die Intensität einige Prozent unter ihre Schwelle fällt, und frühestens nach zwei Takten. Mute und Solo wirken sofort.");

    head ("Genre: Score oder 80er Pop-Rock");
    body ("Die beiden Knöpfe neben STIMMUNG wählen das Vokabular. Score enthält die Wendungen für Filmmusik, von Lauern bis Triumph, orchestral und mit 80er-Synth-Farben. 80er Pop-Rock enthält Powerchord-Riffs, Hi-NRG- und Galopp-Bass, SID-Arpeggios, gehackte Flächen und Hymnen-Wendungen wie ♭VI – ♭VII – I, dazu Disco-Funk und Fernsehmusik um 1980: Septakkorde mit Oktav-Bass, Quintfall-Sequenzen in Moll wie bei einem Teufelsgeiger und sehnsüchtige Balladen. Das Stimmungsfeld funktioniert in beiden gleich: links dunkel, rechts hell, oben aufgewühlt. Alle anderen Funktionen bleiben, auch die eigene Folge, die dann den Pop-Rock-Stil leiht.");
    body ("Im Pop-Rock spielt die Gegenstimme eine durchgehende, gleichbleibende Hook-Linie in Achteln, bei wenig Intensität in Vierteln. Welche Figur, bestimmt VARIATION.");

    head ("WECHSEL");
    body ("Bewegst du den Punkt deutlich, wechselt die Wendung am nächsten Wechselpunkt: am nächsten Schlag (Vorgabe), am nächsten Takt, alle 2 oder alle 4 Takte. Die neue Wendung beginnt dort mit ihrem ersten Akkord. Gehaltene Töne der alten Stimmung enden genau am Wechselpunkt, der Arp läuft im Takt weiter und spielt gleich die neuen Akkordtöne. Kleine Bewegungen lösen keinen Wechsel aus, solange die laufende Wendung noch gut zur Lage passt; die Ebenen reagieren trotzdem sofort auf Intensität und Unruhe.");

    head ("Controller (CC)");
    body ("Stromscore hört auf seinem MIDI-Eingang auf drei Controller: CC 11 für die Färbung, CC 1 für die Intensität und CC 74 für die Unruhe. Das passt zu einem Fader-Controller, wie er für Orchester-Instrumente üblich ist. Gib der Stromscore-Spur den Controller als Eingang und nimm die Fader-Bewegungen als MIDI-Part auf. Über den Knopf mit den CC-Nummern kannst du die Zuordnung ändern oder einzelne Achsen abschalten.");

    head ("Wendungen und Akkorde");
    body ("Rechts oben steht der klingende Akkord, darunter die Wendung und ihre Akkorde. Eine Wendung dauert acht Takte. Welche Wendung kommt, hängt vom Punkt im Feld ab: An jeder Stelle kommen die Wendungen in Frage, die dort gut passen. Sie stehen in der Akkord-Anzeige unter „Hier“, die passendste zuerst. Die Akkorde stehen mit deutschen Notennamen (H statt B); ein Schrägstrich zeigt einen eigenen Basston, etwa D/C.");
    body ("VARIATION bestimmt, welcher dieser Kandidaten in welcher Phrase drankommt und welche der bevorzugten Figuren und Bass-Muster er spielt. Die Stimmung bleibt dabei gleich, nur das Arrangement ändert sich; gleiche Nummer, gleiches Ergebnis. ABWECHSLUNG legt fest, wie viele Kandidaten es gibt: ganz links spielt immer nur die passendste Wendung, weiter rechts mischen sich auch entferntere Nachbarn hinein.");
    body ("Der Vorrat umfasst 48 Wendungen: von Lauern, Trauer, Unruhigem Schlaf und Grusel über Verfolgung, Sog, Achse, Ermittlung, Geheimnis, Wurmloch, Fremde Orte, Synth-Nächte und Funk bis zu Schneelinien, Gleiten, Offenen Quinten, Sehnsucht, Romantik, Terrassen, Erhabenem, Heiterkeit, Western, Abenteuer, Erhebung, Fanfare und Triumph. Im 80er Pop-Rock sind es 36, von Kalter Welle und Feindkontakt über Teufelsgeiger, Vorahnung und Weltraum-Disco bis zu Serenade, Startfreigabe und Stadionhymne.");

    head ("Eigene Folge");
    body ("Mit EIGENE FOLGE spielt Stromscore deine Akkorde statt der Wendungen. Über „Bearbeiten“ legst du bis zu acht Akkorde fest, jeweils mit Grundton, Art (Dur, Moll, maj7, m7, 7, sus4, sus2, add9, m6, m(maj7), m7b5, dim7, +) und Länge in Takten. Die Grundtöne gelten unabhängig von TONART. Vorgabe ist F – C – B – G mit je 2 Takten. Die Akkorde bleiben fest, alles andere bestimmt weiter das Stimmungsfeld: Die Färbung leiht den Stil der Wendung, die am Punkt im Feld liegt, also ihre Figuren, Bass-Muster und den Rhythmus der Fläche. So spielt deine Folge zum Beispiel mit Funk-Bass und Riff oder mit Walking Bass, je nachdem, wohin du den Punkt ziehst. Welcher Stil gerade gilt, steht in der Akkord-Anzeige. Intensität und Unruhe wirken wie sonst. VARIATION wählt bei eigener Folge außerdem die Lage der Fläche: weit, eng oder ohne tiefen Grundton.");

    head ("TONART, TAKT, VARIATION, SWING");
    body ("TONART legt den Grundton fest. TAKT übernimmt die Taktart aus dem Projekt oder legt sie fest (4/4, 3/4, 6/8, 5/4, 7/8, 5/8, 12/8); ungerade Takte bekommen eigene Betonungsgruppen, etwa 3+3+2+2 im 5/4. VARIATION wählt eine von sechzehn Kombinationen aus Wendungen und Figuren; gleiche Nummer, gleiches Ergebnis. SWING verschiebt die Zwischen-Achtel nach hinten, bis zum Triolen-Gefühl.");

    head ("Die fünf Ebenen");
    body ("Oben in jedem Kasten stehen der Name, M (Mute), S (Solo) wie in Studio One und die Lampe, die bei jedem Ton leuchtet. Bei Fläche, Bass und Akzent sind es zwei Lampen, eine je Kanal. Mute lässt die Ebene schweigen, Solo lässt nur die Solo-Ebenen spielen, auch mehrere gleichzeitig. So kannst du zum Beispiel nur mit dem Bass oder nur mit einer Fläche beginnen. Die Beschreibung jeder Ebene steht im Tooltip über ihrem Kasten.");
    body ("Fläche und Bass spielen immer, die anderen Ebenen setzen mit der Intensität ein: Arp ab 25 %, Akzent ab 25 % oder bei Unruhe, Gegenstimme ab 15 %. Ab wann eine Ebene gerade einsetzt, steht im Regler INTENSITÄT hinter dem Wert, etwa „ab 25 %“ oder „immer“. Gemeint ist die Intensität im Stimmungsfeld: Darunter schweigt die Ebene. Beim Akzent stehen zwei Werte, erst der Tupfer, dann der Stich, etwa „ab 25 / 50 %“. Der Regler der Ebene verschiebt diese Schwellen. Der Regler INTENSITÄT unten in jedem Kasten verschiebt die Intensität nur für diese Ebene. In der Mitte folgt sie dem Feld. Weniger macht sie dünner, beim Bass bis zu langen Tönen. Mehr macht sie dichter, beim Bass bis zu durchgehenden Achteln auf einem Ton; die Ebene setzt dann auch bei ruhiger Stimmung ein. Die übrigen Ebenen bleiben dabei, wie das Feld sie vorgibt. Doppelklick setzt den Regler auf die Mitte. Mit AUFBAU kommen die Ebenen am Anfang einer Szene nacheinander dazu (siehe „Szene“).");

    head ("MIDI-Kanäle, lang und kurz");
    body ("Jede Ebene hat ein Auswahlfeld für ihren MIDI-Kanal (1 bis 16). Mehrere Ebenen dürfen sich einen Kanal teilen: Stellst du überall Kanal 1 ein, spielt alles auf einem einzigen Instrument, zum Beispiel einem Klavier. Treffen dabei zwei Ebenen denselben Ton, schneidet keine die andere ab.");
    body ("Fläche und Bass haben zwei Kanäle, LANG und KURZ, denn Orchester-Instrumente brauchen für gehaltene und für kurze Töne verschiedene Patches. Bei der Fläche gehen gehaltene Akkorde auf „Lang“, Schläge, Puls, Staccato und Gated auf „Kurz“. Beim Bass gehen Gehalten, Halbe und Orgelpunkt auf „Lang“, alle anderen Muster auf „Kurz“. Stellst du bei beiden denselben Kanal ein, spielt alles auf einem Instrument.");

    head ("Akzente");
    body ("Der Akzent wirft nur ab und zu etwas ein und bleibt nie stehen. Er hat zwei Stimmen mit eigenem Kanal. Der TUPFER spielt einzelne kurze, hohe Töne auf Zwischenzeiten, für Celesta, Glocken, Harfe oder Pizzicato. Der STICH ist ein einzelner kurzer Schlag an Akkordwechseln, am Ende einer Phrase und als Antwort kurz nach einem Tupfer; er kündigt auch das harte Ende und das Ziel einer Fahrt an und setzt den Schlussschlag. Bei wenig Intensität spielt nur der Tupfer, ab 50 % kommt der Stich dazu, bei viel Intensität schlagen am Phrasenende beide zugleich. Im Pop-Rock setzt der Stich zusätzlich Stabs auf die Zwischenzeit. Bei Unruhe kommt in der Mitte jedes Akkords ein fremder, reibender Ton hinzu. Gibst du beiden Akzenten denselben Kanal, spielen sie auf einem Instrument.");
    body ("Der Knopf unter dem Kanal des Stichs öffnet ein Fenster mit zwei Arten. FEST (Vorgabe): Der Stich spielt immer dieselbe Taste, unabhängig von Akkord, Oktave und Tonumfang. Das passt für ein perkussives Sample, etwa eine Pauke oder große Trommel, das in deiner Library auf genau einer Taste liegt. Die Taste wählst du aus der Liste oder lernst sie an: „Taste anlernen“ klicken und die Taste auf dem Keyboard drücken. „Hören“ schlägt sie einmal an. AKKORD: Der Stich spielt den Grundton des aktuellen Akkords in tiefer Mittellage, für Klavier, Synth-Stab oder Pizzicato-Bass; dafür gibt es dort auch den Tonumfang. Im Knopf steht, was gilt, etwa „Fest: C1“.");

    head ("Muster");
    body ("Fläche: Gehalten, Schläge (kurze Akkorde auf der Zwischenzeit), Puls (auf jedem Schlag), Staccato (kurz auf jedem Schlag) oder Gated (gehackte Achtel). Bass: Gehalten, Halbe, Viertel, Achtel, Puls (durchgehende Sechzehntel auf einem Ton), Funk (synkopiert, mit kurzem Sprung nach oben am Taktende), Pendel (Grundton und kleine Terz, bei Unruhe Halbton), Walking (Akkordtöne in Vierteln, chromatisch zum nächsten Grundton), Wechselbass (Grundton und Quinte im Wechsel), Herzschlag (doppelter Schlag, wie ein Puls), Arpeggio (Akkordtöne in Achteln), Orgelpunkt (liegt auf dem Grundton der Wendung, während die Akkorde darüber wandern), Hi-NRG (Grundton und Oberoktave im Wechsel) oder Galopp (Achtel und zwei Sechzehntel). Arp: Aufwärts, Abwärts, Kreisend (auf und ab), Zelle (kurze, obsessive Figur), Riff, Glitzern (schnell und hoch), Sprünge (weite Dreiklangs-Sprünge), Kaskade (Harfen-Wellen in Dreiergruppen), Oktatonisch (Läufe auf der Halbton-Ganzton-Leiter), Quarten (gestapelte Quarten als Ostinato) oder SID (Dreiklang in Sechzehnteln wie auf dem C64); das Tempo wählst du darunter. Auf Auto folgt das Muster der Wendung.");

    head ("Nächster Akkord und Feld-Karte");
    body ("Rechts oben in der Akkord-Anzeige steht der nächste Akkord, darunter läuft eine dünne Leiste bis zum Wechsel. Fährst du mit der Maus über das Stimmungsfeld, ohne zu klicken, erscheinen klein die Wendungen, die dort am nächsten liegen.");

    head ("MIDI herausziehen");
    body ("Das Feld MIDI neben VORHÖREN ziehst du auf deine DAW: Es entsteht eine MIDI-Datei mit den nächsten Takten, eine Spur je eingestelltem MIDI-Kanal, benannt nach den Ebenen darauf, mit allen aktuellen Einstellungen. Stumme Ebenen bleiben leer, mit Solo ziehst du also auch einzelne Ebenen heraus. Ein Klick auf das Feld wechselt die Länge zwischen 8, 16 und 32 Takten. Ist die Dynamik eingeschaltet, sind die Dynamikkurven mit in der Datei.");

    head ("Dynamik per CC");
    body ("Im Menü des CC-Knopfs schaltest du unter „Ausgabe an die Spuren“ die Dynamik ein. Dann bekommt jeder benutzte Kanal CC 1 (Dynamik) und CC 11 (Ausdruck), wie es Orchester-Libraries erwarten; beide Nummern lassen sich dort ändern oder abschalten. Der Grundwert folgt der Intensität, darauf liegen atmende Bögen von einem bis vier Vierteln, im Score weiter und bei Unruhe mit einem Akzent beim Akkordwechsel, im Pop-Rock fast flach. Das ist getrennt von den Controllern am Eingang: Dein Controller bewegt das Stimmungsfeld, die Ausgabe geht an deine Instrumente. Für Synth-Klänge lässt du die Dynamik besser aus, weil CC 1 dort oft ein Vibrato steuert.");

    head ("Gegenstimme");
    body ("Die fünfte Ebene ist die einzige lange Linie, gedacht für Horn, Cello, Oboe oder ein Lead-Instrument. Sie liegt in der Mitte, zwischen Tupfer und Stich, damit sich nichts überschneidet. Sie geht schrittweise auf Akkordtönen von Akkord zu Akkord und bevorzugt Terz und Septime. In dunkler Färbung neigt sie nach unten, in heller nach oben. Bei wenig Intensität wechselt sie nur mit den Akkorden, bei mehr alle zwei Takte, aufgewühlt in Halben. Bei Unruhe kommt sie mit einem Vorhalt von oben in den Akkord. Mit LEGATO überlappen die Töne um eine Sechzehntelnote, damit Legato-Instrumente sie gebunden spielen; ohne setzen sie kurz vor dem nächsten Ton ab. Sie ist keine fertige Melodie, sondern ein roter Faden für deine eigene.");
    body ("Mit MOTIV spielt die Gegenstimme am Anfang jeder Phrase eine kurze Figur aus drei bis fünf Tönen, die ersten zwei Takte lang. Die Figur ist gewürfelt (NEU WÜRFELN bei SZENE) und kehrt wieder, im Wechsel der Phrasen abgewandelt: wie zuvor, einen Akkordton höher, mit umgekehrter Richtung, mit höherem Schluss. Die Töne sind Stufen auf den Akkordtönen, so passt sich die Figur jeder Harmonie an. Bei wenig Intensität fallen die letzten Töne weg. Danach geht die ruhige Linie weiter. Im Pop-Rock spielt statt des Motivs die Hook-Linie.");

    head ("Durchgänge");
    body ("Mit DURCHGÄNGE erklingt bei viel Intensität (ab 60 %) auf dem letzten Schlag eines Akkords kurz die Dominante des nächsten Akkords. Das zieht in den Wechsel hinein. Es gilt für Wendungen und eigene Folge und lässt sich jederzeit abschalten.");

    head ("Satz der Fläche");
    body ("Die Fläche ist weit gesetzt wie im Orchester: Grundton und Quinte unten, Terz und Farbtöne eine Oktave höher, bei viel Intensität mit Verdopplung oben.");

    head ("Oktave");
    body ("Jede Ebene hat ihre eigene Oktavlage: Normal, eine oder zwei Oktaven höher oder tiefer. So passt du die Lage an deine Instrumente an, ohne die Noten zu verändern.");

    head ("Tonumfang");
    body ("Orchesterinstrumente können nur einen bestimmten Bereich spielen, ein Synth spielt alles. Unten in jedem Ebenen-Kasten steht deshalb neben der Oktave „Umfang“, beim Akzent je eine eigene Zeile für Tupfer und Stich. Ein Klick öffnet ein kleines Fenster: Dort schaltest du die Begrenzung ein und legst den tiefsten und den höchsten Ton fest. Das mittlere C heißt hier wie in Studio One C3, in Klammern steht die MIDI-Nummer.");
    body ("Für den Anfang gibt es Vorlagen für übliche Instrumente, von Violine bis Klavier. Genauer geht es mit ANLERNEN: Klicken, dann auf dem Keyboard die tiefste und die höchste Taste drücken, die dein Patch spielen kann. Die Reihenfolge ist egal. Dein Keyboard muss dafür auf die Spur mit Stromscore geleitet sein. Danach steht der Bereich im Knopf, zum Beispiel C3–C6.");
    body ("Damit du dabei dein Instrument hörst, gibt es im Fenster KEYBOARD DURCHLEITEN. Solange das Fenster offen ist, gehen deine Tasten auf den MIDI-Kanal dieser Ebene (bei Fläche und Bass auf beide Kanäle). So suchst du am eigenen Patch, wo der spielbare Bereich beginnt und endet oder auf welcher Taste ein Sample liegt, und lernst es gleich an. Schließt du das Fenster, hört das Durchleiten auf, und alle gehaltenen Töne enden. Außerhalb des Fensters werden eingehende Noten nie weitergereicht.");
    body ("Es fällt kein Ton weg. Ein Akkord rückt als Ganzes in den Bereich, einzelne Töne außerhalb wandern um ganze Oktaven nach innen. Ein Arpeggio kehrt an den Grenzen um und spielt jeden Schritt weiter. Die Gegenstimme sucht ihre Linie von vornherein im Bereich. Die Oktav-Einstellung wirkt zuerst, der Tonumfang ist die feste Grenze. Ist der Bereich enger als eine Oktave, ersetzen Akkordtöne im Bereich die Töne, die nicht hineinpassen. Auch die herausgezogene MIDI-Datei hält sich an den Tonumfang.");

    head ("Folgt den Akkorden / bleibt");
    body ("Bei Fläche, Bass und Arp bestimmt dieser Schalter, ob die Ebene den Akkordwechseln folgt oder auf dem Grundakkord der Tonart bleibt. Ein Arp, der bleibt, läuft unverändert durch, während sich Fläche und Bass bewegen. Ein Bass, der bleibt, hält den Grundton unter wechselnden Akkorden.");

    head ("VORHÖREN");
    body ("Ein einfacher Testklang im Plugin, damit du ohne eigene Instrumente hörst, was entsteht. Das geht auch bei stehender DAW: Ist VORHÖREN an und die Wiedergabe gestoppt, läuft Stromscore mit eigener Uhr im Projekttempo. Dabei klingt nur der Testklang, an deine Instrumentenspuren geht kein MIDI. Startest du die Wiedergabe, übernimmt der Takt des Projekts. Für die fertige Musik schaltest du VORHÖREN aus.");

    head ("Allgemein");
    body ("Doppelklick auf einen Drehregler oder Strg-Klick setzt ihn auf den Standardwert zurück. Look: Dunkel / Hell umschalten, die Wahl wird mit dem Projekt gespeichert. Das Fenster ist am rechten unteren Rand skalierbar (50–300 %).");
    note ("Bei Stopp, Sprung, Reset oder Bypass werden alle klingenden Noten beendet, zusätzlich geht auf jedem Kanal ein „Alle Noten aus“ hinaus. Das Ergebnis hängt nur vom Start der Szene, der Projektposition und den Einstellungen ab, nicht von der Puffergröße.");

    head ("Idee und Konzept");
    body ("Lars Eickstädt, Stromschlag Audio");
    note ("Gebaut mit JUCE.");
    return s;
}

// ---------------------------------------------------------------- Editor

StromscoreEditor::StromscoreEditor (StromscoreProcessor& p) : AudioProcessorEditor (&p), processor (p)
{
    addAndMakeVisible (content);
    setResizable (true, true);
    setResizeLimits (kBaseW / 2, kBaseH / 2, kBaseW * 3, kBaseH * 3);
    if (auto* c = getConstrainer())
        c->setFixedAspectRatio ((double) kBaseW / (double) kBaseH);

    logo = juce::ImageCache::getFromMemory (BinaryData::logo_png, BinaryData::logo_pngSize);
    theme = processor.uiTheme.load() == 1 ? lightTheme() : darkTheme();
    setLookAndFeel (&look);

    auto label = [this] (juce::Label& l, const juce::String& t, juce::Justification j)
    {
        l.setText (t, juce::dontSendNotification);
        l.setJustificationType (j);
        content.addAndMakeVisible (l);
    };
    label (padLabel, u8 ("STIMMUNG"), juce::Justification::centredLeft);
    label (keyLabel, "TONART", juce::Justification::centredLeft);
    label (meterLabel, "TAKT", juce::Justification::centredLeft);
    label (variationLabel, "VARIATION", juce::Justification::centredLeft);
    label (swingLabel, "SWING", juce::Justification::centredLeft);
    label (chordLabel, "AKKORD", juce::Justification::centredLeft);
    label (changeLabel, "WECHSEL", juce::Justification::centredLeft);
    label (customLabel, "AKKORDE", juce::Justification::centredLeft);

    // Stimmungsfeld: Faerbung und Intensitaet als ein Zug, Unruhe per Mausrad
    for (int a = 0; a < 3; ++a)
        axisAttachment[a] = std::make_unique<juce::ParameterAttachment> (*processor.apvts.getParameter (StromscoreProcessor::kAxisIds[a]),
            [this, a] (float v)
            {
                (a == 0 ? pad.x : a == 1 ? pad.y : pad.z) = v;
                pad.repaint();
            }, nullptr);
    pad.onDragStart = [this] { processor.beginManualPosition(); axisAttachment[0]->beginGesture(); axisAttachment[1]->beginGesture(); };
    pad.onDrag = [this] (float nx, float ny) { axisAttachment[0]->setValueAsPartOfGesture (nx); axisAttachment[1]->setValueAsPartOfGesture (ny); };
    pad.onDragEnd = [this] { axisAttachment[0]->endGesture(); axisAttachment[1]->endGesture(); };
    pad.onWheel = [this] (float dz) { axisAttachment[2]->setValueAsCompleteGesture (juce::jlimit (0.0f, 1.0f, pad.z + dz)); };
    pad.onHover = [this] (float hx, float hy)
    {
        auto st = processor.currentSettings();
        st.x = hx; st.y = hy; st.variety = 1.0f;
        int c[3];
        const int n = stromscore::Generator::candidates (st, c, 3);
        pad.numHover = n;
        for (int i = 0; i < n; ++i)
        {
            const auto& wd = stromscore::wendungAt (st.genre, c[i]);
            pad.hover[i] = { juce::String (juce::CharPointer_UTF8 (wd.name)), wd.x, wd.y };
        }
        pad.repaint();
    };

    // Genre: Score oder 80er Pop-Rock
    genreScore.setButtonText ("Score");
    genrePop.setButtonText ("Pop-Rock");
    for (auto* b : { &genreScore, &genrePop }) { b->setRadioGroupId (77); content.addAndMakeVisible (b); }
    genreAttachment = std::make_unique<juce::ParameterAttachment> (*processor.apvts.getParameter ("genre"),
        [this] (float v)
        {
            const bool pop = juce::roundToInt (v) == 1;
            genreScore.setToggleState (! pop, juce::dontSendNotification);
            genrePop.setToggleState (pop, juce::dontSendNotification);
        }, nullptr);
    genreScore.onClick = [this] { genreAttachment->setValueAsCompleteGesture (0.0f); };
    genrePop.onClick = [this] { genreAttachment->setValueAsCompleteGesture (1.0f); };
    genreAttachment->sendInitialUpdate();
    genreScore.setTooltip (u8 ("Vokabular für Filmmusik: Wendungen von Lauern bis Triumph, orchestral und mit 80er-Synth-Farben."));
    genrePop.setTooltip (u8 ("Vokabular für 80er Pop-Rock: Powerchords, Hi-NRG- und Galopp-Bass, SID-Arpeggios, gehackte Flächen, eine durchgehende Hook-Linie. Alle anderen Funktionen bleiben gleich."));

    // MIDI herausziehen
    midiDrag.render = [this] { return processor.renderMidiFile (processor.exportBars.load()); };
    midiDrag.onClick = [this]
    {
        const int now = processor.exportBars.load();
        processor.exportBars.store (now == 8 ? 16 : now == 16 ? 32 : 8);
        processor.updateHostDisplay (juce::AudioProcessorListener::ChangeDetails{}.withNonParameterStateChanged (true));
        updateMidiLabel();
    };
    content.addAndMakeVisible (midiDrag);
    updateMidiLabel();
    for (auto& a : axisAttachment) a->sendInitialUpdate();
    content.addAndMakeVisible (pad);


    variation.setSliderStyle (juce::Slider::IncDecButtons);
    variation.setTextBoxStyle (juce::Slider::TextBoxLeft, false, 60, 24);
    content.addAndMakeVisible (variation);
    variationAttachment = std::make_unique<APVTS::SliderAttachment> (processor.apvts, "variation", variation);

    swing.setSliderStyle (juce::Slider::LinearHorizontal);
    swing.setTextBoxStyle (juce::Slider::TextBoxRight, false, 50, 20);
    content.addAndMakeVisible (swing);
    swingAttachment = std::make_unique<APVTS::SliderAttachment> (processor.apvts, "swing", swing);

    keyBox.addItemList (StromscoreProcessor::keyNames(), 1);
    meterBox.addItemList (StromscoreProcessor::meterNames(), 1);
    content.addAndMakeVisible (keyBox);
    content.addAndMakeVisible (meterBox);
    keyAttachment = std::make_unique<APVTS::ComboBoxAttachment> (processor.apvts, "key", keyBox);
    meterAttachment = std::make_unique<APVTS::ComboBoxAttachment> (processor.apvts, "takt", meterBox);

    label (varietyLabel, "ABWECHSLUNG", juce::Justification::centredLeft);
    variety.setSliderStyle (juce::Slider::LinearHorizontal);
    variety.setTextBoxStyle (juce::Slider::TextBoxRight, false, 50, 20);
    content.addAndMakeVisible (variety);
    varietyAttachment = std::make_unique<APVTS::SliderAttachment> (processor.apvts, "abwechslung", variety);
    variety.setTooltip (u8 ("Wie viele passende Wendungen sich abwechseln. Ganz links: immer nur die passendste. Weiter rechts: auch entferntere Nachbarn. Welche gerade in Frage kommen, steht in der Akkord-Anzeige unter „Hier“."));

    changeBox.addItemList (StromscoreProcessor::changeNames(), 1);
    content.addAndMakeVisible (changeBox);
    changeAttachment = std::make_unique<APVTS::ComboBoxAttachment> (processor.apvts, "wechsel", changeBox);

    // Eigene Akkordfolge
    customButton.setClickingTogglesState (true);
    customButton.setButtonText ("Eigene Folge");
    content.addAndMakeVisible (customButton);
    customAttachment = std::make_unique<APVTS::ButtonAttachment> (processor.apvts, "eigeneFolge", customButton);
    infoButton.setButtonText ("Wendungsinfo"); infoButton.setName ("Wendungsinfo");
    infoButton.setTooltip (u8 ("Alle 48 Score- und 36 Pop-Rock-Wendungen: Harmonik, Muster, Instrumentierung und stilistische Bezüge."));
    infoButton.onClick = [this] { showWendungInfo(); }; content.addAndMakeVisible (infoButton);
    editButton.setButtonText (u8 ("…"));
    editButton.setName ("Bearbeiten");
    passingButton.setButtonText (u8 ("Durchgänge"));
    passingButton.setClickingTogglesState (true);
    content.addAndMakeVisible (passingButton);
    passingAttachment = std::make_unique<APVTS::ButtonAttachment> (processor.apvts, "durchgaenge", passingButton);
    passingButton.setTooltip (u8 ("Bei viel Intensität (ab 60 %) erklingt auf dem letzten Schlag eines Akkords kurz die Dominante des nächsten Akkords, als Durchgang. Gilt für Wendungen und eigene Folge."));
    editButton.onClick = [this] { slots.setVisible (! slots.isVisible()); if (slots.isVisible()) slots.toFront (false); };
    content.addAndMakeVisible (editButton);
    for (int i = 0; i < stromscore::kMaxChords; ++i)
    {
        const juce::String n (i + 1);
        slots.root[i].addItemList (StromscoreProcessor::slotRootNames(), 1);
        slots.type[i].addItemList (StromscoreProcessor::slotTypeNames(), 1);
        slots.bars[i].addItemList (StromscoreProcessor::slotBarNames(), 1);
        slotAttachment[3 * i] = std::make_unique<APVTS::ComboBoxAttachment> (processor.apvts, "slotRoot" + n, slots.root[i]);
        slotAttachment[3 * i + 1] = std::make_unique<APVTS::ComboBoxAttachment> (processor.apvts, "slotType" + n, slots.type[i]);
        slotAttachment[3 * i + 2] = std::make_unique<APVTS::ComboBoxAttachment> (processor.apvts, "slotBars" + n, slots.bars[i]);
        slots.root[i].setTooltip (u8 ("Grundton des Akkords (unabhängig von TONART)."));
        slots.type[i].setTooltip (u8 ("Art des Akkords."));
        slots.bars[i].setTooltip (u8 ("Länge in Takten. „–“ lässt den Platz aus."));
    }
    slots.doneButton.setButtonText ("Fertig");
    slots.doneButton.onClick = [this] { slots.setVisible (false); };
    slots.setVisible (false);
    content.addChildComponent (slots);

    ccButton.onClick = [this] { showCcMenu(); };
    content.addAndMakeVisible (ccButton);
    updateCcButton();

    previewButton.setButtonText (u8 ("Vorhören"));
    previewButton.setClickingTogglesState (true);
    content.addAndMakeVisible (previewButton);
    previewAttachment = std::make_unique<APVTS::ButtonAttachment> (processor.apvts, "preview", previewButton);
    content.addAndMakeVisible (chordDisplay);
    // Balken in der Akkord-Anzeige: ziehen wie im Stimmungsfeld
    chordDisplay.onBarStart = [this] (int axis) { if (axis < 2) processor.beginManualPosition(); axisAttachment[axis]->beginGesture(); };
    chordDisplay.onBar = [this] (int axis, float v) { axisAttachment[axis]->setValueAsPartOfGesture (v); };
    chordDisplay.onBarEnd = [this] (int axis) { axisAttachment[axis]->endGesture(); };

    // Ebenen
    static const int firstOut[stromscore::kNumLayers] = { stromscore::OutPadLong, stromscore::OutBassLong, stromscore::OutArp, stromscore::OutTupfer, stromscore::OutCounter };
    for (int i = 0; i < stromscore::kNumLayers; ++i)
    {
        auto& lv = layers[i];
        const juce::String n (i + 1);
        lv.title = u8 (kLayerTitle[i]);
        lv.index = i;
        const bool two = i == stromscore::kFlaeche || i == stromscore::kBass || i == stromscore::kAkzent;
        lv.numLamps = two ? 2 : 1;
        lv.setTooltip (u8 (kLayerTip[i]));

        // MIDI-Kanaele
        for (int c = 0; c < (two ? 2 : 1); ++c)
        {
            const int o = firstOut[i] + c;
            lv.chanBox[c].addItemList (StromscoreProcessor::channelNames(), 1);
            lv.chanBox[c].setVisible (true);
            channelAttachment[o] = std::make_unique<APVTS::ComboBoxAttachment> (processor.apvts, "kanal" + juce::String (o + 1), lv.chanBox[c]);
        }
        if (i == stromscore::kFlaeche || i == stromscore::kBass)
        {
            lv.rowLabel[0] = "Lang"; lv.rowLabel[1] = "Kurz";
            const auto what = i == stromscore::kFlaeche ? u8 ("gehaltene Akkorde") : u8 ("Gehalten, Halbe und Orgelpunkt");
            lv.chanBox[0].setTooltip (u8 ("MIDI-Kanal für die langen Töne: ") + what + u8 (". Zum Beispiel ein Sustain-Patch."));
            lv.chanBox[1].setTooltip (u8 ("MIDI-Kanal für die kurzen Töne: alle übrigen Muster. Zum Beispiel ein Staccato- oder Spiccato-Patch. Derselbe Kanal wie bei „Lang“: alles auf einem Instrument."));
        }
        else if (i == stromscore::kAkzent)
        {
            lv.rowLabel[0] = "Tupfer"; lv.rowLabel[2] = "Stich";
            lv.chanBox[0].setTooltip (u8 ("MIDI-Kanal für den Tupfer: einzelne kurze hohe Töne, etwa Celesta, Glocken oder Pizzicato."));
            lv.chanBox[1].setTooltip (u8 ("MIDI-Kanal für den Stich: ein einzelner kurzer Schlag, etwa Pauke, große Trommel, Klavier oder Synth-Stab. Derselbe Kanal wie beim Tupfer: beide Akzente auf einem Instrument."));
        }
        else
        {
            lv.rowLabel[0] = "Kanal";
            lv.chanBox[0].setTooltip (u8 ("MIDI-Kanal dieser Ebene. Mehrere Ebenen dürfen sich einen Kanal teilen, etwa alles auf Kanal 1 für ein einziges Klavier."));
        }

        lv.octBox.addItemList (StromscoreProcessor::octaveNames(), 1);
        lv.octBox.setTooltip (u8 ("Oktavlage dieser Ebene."));
        octaveAttachment[i] = std::make_unique<APVTS::ComboBoxAttachment> (processor.apvts, "oct" + n, lv.octBox);

        // Tonumfang: je Ebene, beim Akzent getrennt fuer Tupfer und Stich
        const int r0 = i;
        lv.rangeButton.setVisible (true);
        lv.rangeButton.setName ("Umfang" + juce::String (r0 + 1));
        lv.rangeButton.onClick = [this, r0] { showRangePanel (r0); };
        lv.rangeButton.setTooltip (u8 ("Tonumfang: auf den spielbaren Bereich des Instruments begrenzen, mit Vorlagen und Anlernen per Keyboard."));
        if (i == stromscore::kAkzent)
        {
            lv.rangeButton.setTooltip (u8 ("Tonumfang des Tupfers: auf den spielbaren Bereich des Instruments begrenzen, mit Vorlagen und Anlernen per Keyboard."));
            lv.rangeButton2.setTooltip (u8 ("Ton des Stichs: Fest auf einer Taste (Vorgabe, für ein perkussives Sample) oder Grundton des Akkords mit eigenem Tonumfang. Im Fenster lässt sich die Taste anlernen und anhören."));
            lv.rangeButton2.setVisible (true);
            lv.rangeButton2.setName ("Umfang6");
            lv.rangeButton2.onClick = [this] { showRangePanel (5); };
        }

        lv.muteButton.setButtonText ("M");
        lv.soloButton.setButtonText ("S");
        lv.soloButton.setClickingTogglesState (true);
        lv.muteButton.setClickingTogglesState (true);
        lv.soloButton.setTooltip (u8 ("Solo: nur diese Ebene spielt (mehrere Ebenen können gleichzeitig solo sein)."));
        lv.muteButton.setTooltip (u8 ("Mute: diese Ebene schweigt."));
        soloAttachment[i] = std::make_unique<APVTS::ButtonAttachment> (processor.apvts, "solo" + n, lv.soloButton);
        muteAttachment[i] = std::make_unique<APVTS::ButtonAttachment> (processor.apvts, "mute" + n, lv.muteButton);
        lv.intensity.setSliderStyle (juce::Slider::LinearBar);
        lv.intensity.setTextValueSuffix ("");
        intensityAttachment[i] = std::make_unique<APVTS::SliderAttachment> (processor.apvts, "intensitaet" + n, lv.intensity);
        lv.intensity.textFromValueFunction = [this, i] (double v)
        {
            const int p = juce::roundToInt (v * 100.0);
            auto t = u8 ("Intensität ") + (p > 0 ? juce::String ("+") : p < 0 ? u8 ("−") : u8 ("±")) + juce::String (std::abs (p)) + " %";
            if (layers[i].entry.isNotEmpty()) t << u8 (" · ") << layers[i].entry;
            return t;
        };
        lv.intensity.updateText();
        lv.intensity.setDoubleClickReturnValue (true, 0.0);
        lv.intensity.setTooltip (u8 ("Intensität nur für diese Ebene, zusätzlich zum Stimmungsfeld. Mitte: wie das Feld. Weniger: dünner, bis zu langen Tönen. Mehr: dichter, bis zu durchgehenden Achteln; die Ebene setzt dann auch bei ruhiger Stimmung ein. Hinter dem Wert steht, ab wann die Ebene gerade einsetzt. Doppelklick: Mitte."));
        if (i < 3)
        {
            lv.followButton.setVisible (true);
            lv.followButton.setClickingTogglesState (true);
            lv.followButton.onStateChange = [this, i]
            { layers[i].followButton.setButtonText (layers[i].followButton.getToggleState() ? u8 ("folgt den Akkorden") : u8 ("bleibt auf Grundakkord")); };
            lv.followButton.setTooltip (u8 ("Ein: die Ebene folgt den Akkordwechseln. Aus: sie bleibt auf dem Grundakkord der Tonart, zum Beispiel ein durchlaufender Arp oder ein Bass auf dem Grundton."));
            followAttachment[i] = std::make_unique<APVTS::ButtonAttachment> (processor.apvts, "follow" + juce::String (i + 1), lv.followButton);
            lv.combo1.setVisible (true);
            lv.rowLabel[2] = "Muster";
        }
        content.addAndMakeVisible (lv);
    }
    layers[2].rowLabel[1] = "Tempo";
    layers[4].legatoButton.setVisible (true);
    layers[4].legatoButton.setClickingTogglesState (true);
    layers[4].legatoButton.setTooltip (u8 ("An: jeder Ton klingt bis zum nächsten und überlappt ihn um eine Sechzehntelnote, so spielen Legato-Patches gebunden. Aus: die Töne setzen kurz vor dem nächsten ab."));
    legatoAttachment = std::make_unique<APVTS::ButtonAttachment> (processor.apvts, "legato", layers[4].legatoButton);
    layers[4].rowLabel[1] = "Linie";
    layers[4].legatoButton.setButtonText ("Legato");
    layers[4].motifButton.setVisible (true);
    layers[4].motifButton.setClickingTogglesState (true);
    layers[4].motifButton.setButtonText ("Motiv");
    layers[4].motifButton.setTooltip (u8 ("Motiv: am Anfang jeder Phrase spielt die Gegenstimme eine kurze Figur aus drei bis fünf Tönen, gewürfelt mit „Neu würfeln“. Sie kehrt wieder und wird abgewandelt: wie zuvor, einen Akkordton höher, umgekehrt, mit höherem Schluss. Die Töne folgen der Harmonie. Bei wenig Intensität fallen die letzten Töne weg. Aus: nur die ruhige Linie."));
    motifAttachment = std::make_unique<APVTS::ButtonAttachment> (processor.apvts, "motiv", layers[4].motifButton);

    // Szene: Aufbau, Einstieg, Wurf, Haerte, Laenge, Ende
    auto small = [this] (juce::Label& l, const juce::String& t)
    {
        l.setText (t, juce::dontSendNotification);
        l.setJustificationType (juce::Justification::centredLeft);
        l.setFont (juce::FontOptions (11.5f));
        content.addAndMakeVisible (l);
    };
    small (sceneLabel, "SZENE"); small (driveLabel, "FAHRT");
    small (entryLabel, "Einstieg"); small (lengthLabel, u8 ("Länge")); small (endLabel, "Ende");
    small (startLabel, "Start"); small (durLabel, "Dauer"); small (curveLabel, "Kurve");
    small (sceneStatus, {});
    sceneStatus.setFont (juce::FontOptions (12.0f));
    sceneStatus.setMinimumHorizontalScale (0.75f);
    for (auto* b : { &sceneButton, &driveButton }) { b->setClickingTogglesState (true); content.addAndMakeVisible (b); }
    sceneButton.setButtonText ("Aufbau");
    driveButton.setButtonText ("Fahrt");
    sceneAttachment = std::make_unique<APVTS::ButtonAttachment> (processor.apvts, "aufbau", sceneButton);
    driveAttachment = std::make_unique<APVTS::ButtonAttachment> (processor.apvts, "fahrt", driveButton);
    diceButton.setButtonText (u8 ("Neu würfeln"));
    diceButton.onClick = [this]
    {
        if (auto* prm = processor.apvts.getParameter ("wurf"))
        {
            const int now = juce::roundToInt (processor.apvts.getRawParameterValue ("wurf")->load());
            prm->beginChangeGesture();
            prm->setValueNotifyingHost (prm->convertTo0to1 ((float) ((now + 1) % 10000)));
            prm->endChangeGesture();
        }
    };
    content.addAndMakeVisible (diceButton);
    auto box = [this] (juce::ComboBox& b, const juce::StringArray& items, std::unique_ptr<APVTS::ComboBoxAttachment>& att, const char* id)
    {
        b.addItemList (items, 1);
        content.addAndMakeVisible (b);
        att = std::make_unique<APVTS::ComboBoxAttachment> (processor.apvts, id, b);
    };
    box (buildBox, StromscoreProcessor::buildNames(), buildAttachment, "aufbauTakte");
    box (entryBox, StromscoreProcessor::entryNames(), entryAttachment, "einstieg");
    box (lengthBox, StromscoreProcessor::sceneLengthNames(), lengthAttachment, "szenenLaenge");
    box (endBox, StromscoreProcessor::endingNames(), endAttachment, "ende");
    box (startBox, StromscoreProcessor::driveStartNames(), startAttachment, "fahrtStart");
    box (durBox, StromscoreProcessor::driveBarsNames(), durAttachment, "fahrtTakte");
    box (curveBox, StromscoreProcessor::curveNames(), curveAttachment, "fahrtKurve");
    hardness.setSliderStyle (juce::Slider::LinearBar);
    content.addAndMakeVisible (hardness);
    hardnessAttachment = std::make_unique<APVTS::SliderAttachment> (processor.apvts, "haerte", hardness);
    hardness.textFromValueFunction = [] (double v)
    {
        const int p = juce::roundToInt (v * 100.0);
        return u8 ("Härte ") + juce::String (p) + " %" + (p < 40 ? u8 (" · weich") : p > 60 ? u8 (" · hart") : juce::String());
    };
    hardness.updateText();
    hardness.setDoubleClickReturnValue (true, 0.5);

    sceneButton.setTooltip (u8 ("Aufbau: Die Szene beginnt mit dem Start der Wiedergabe. Zuerst spielt nur die Ebene des Einstiegs, die anderen folgen nacheinander auf Taktgrenzen, bis nach der eingestellten Zahl von Takten alles da ist. Dabei wird die Musik dichter. Aus: alle Ebenen setzen gleich ein."));
    buildBox.setTooltip (u8 ("Wie lange der Aufbau dauert: 4, 8 oder 16 Takte bis alle Ebenen spielen."));
    entryBox.setTooltip (u8 ("Womit die Szene beginnt: ein leiser Akkord der Fläche, ein Bass-Schlag, ein Puls in Vierteln, das Arpeggio, ein Akzent in der Stille, die Gegenstimme oder alles zugleich. Danach folgen die verwandten Ebenen. Auto würfelt passend zu Genre und Stimmung, nur aus Ebenen, die gerade spielen können."));
    diceButton.setTooltip (u8 ("Neuer Wurf: ein anderer Einstieg bei Auto und ein anderes Motiv der Gegenstimme. Gleicher Wurf, gleiches Ergebnis; er wird mit dem Projekt gespeichert."));
    hardness.setTooltip (u8 ("Wie die Ebenen einsetzen. Unter 50 % weich eingeblendet (ganz links über zwei Takte), über 50 % mit einem kräftigen ersten Anschlag. Gilt auch, wenn eine Ebene mit steigender Intensität dazukommt. Doppelklick: Mitte."));
    lengthBox.setTooltip (u8 ("Länge der Szene ab dem Start der Wiedergabe. Unbegrenzt: die Musik läuft weiter. Mit Länge endet sie nach dieser Zahl von Takten, wie unter „Ende“ eingestellt."));
    endBox.setTooltip (u8 ("Hart: Bis zum Schluss spielen alle Ebenen, im letzten Takt zieht sich der Bass zurück und ein Stich kündigt an, dann ein kurzer, kräftiger Schlag und Stille. Ausklingend: Die Ebenen gehen nacheinander, was zuletzt kam, zuerst; die erste Ebene klingt bis zum Ende. Offen: Die Musik wird zum Schluss noch dichter und bricht dann ohne Schlussschlag ab."));
    driveButton.setTooltip (u8 ("Fahrt von A nach B: Die Musik wandert selbst vom Punkt im Feld (A) zum Ziel (B). Links setzt/zieht immer A und übernimmt manuell, rechts setzt/zieht immer B, ohne die Fahrt zu starten. B bleibt sichtbar und wird im Projekt gespeichert. Während der Hinfahrt führt ein geändertes B ohne Positionssprung zum neuen Ziel. Führt die Fahrt nach oben, bereitet die Musik das Ziel vor: Der Bass zieht sich zurück, ein Stich kündigt an, am Ziel setzen alle Ebenen kräftig ein. Am Ziel wird B zum neuen A und die Fahrt schaltet sich aus; unterwegs ausgeschaltet bleibt die Musik, wo sie gerade ist."));
    startBox.setTooltip (u8 ("Wann die Fahrt beginnt, gezählt ab dem Start der Wiedergabe."));
    durBox.setTooltip (u8 ("Wie lange die Fahrt von A nach B dauert."));
    curveBox.setTooltip (u8 ("Gleichmäßig; erst langsam, dann schnell; in vier Stufen; oder hin und zurück (zur Mitte der Dauer bei B, am Ende wieder bei A)."));
    sceneStatus.setTooltip (u8 ("Stand der Szene: Takt seit dem Start der Wiedergabe, Einstieg, Aufbau, Fahrt und wie viele Takte bis zum Ende bleiben."));

    for (int a = 0; a < 2; ++a)
        targetAttachment[a] = std::make_unique<juce::ParameterAttachment> (*processor.apvts.getParameter (a == 0 ? "fahrtX" : "fahrtY"),
            [this, a] (float v) { (a == 0 ? pad.bx : pad.by) = v; pad.repaint(); }, nullptr);
    for (auto& t : targetAttachment) t->sendInitialUpdate();
    pad.targetPending = processor.targetSet.load();
    pad.onSetTarget = [this] { processor.markTargetSet(); pad.targetPending = true; pad.repaint(); };
    pad.onDragStartB = [this] { targetAttachment[0]->beginGesture(); targetAttachment[1]->beginGesture(); };
    pad.onDragB = [this] (float nx, float ny) { targetAttachment[0]->setValueAsPartOfGesture (nx); targetAttachment[1]->setValueAsPartOfGesture (ny); };
    pad.onDragEndB = [this] { targetAttachment[0]->endGesture(); targetAttachment[1]->endGesture(); };
    layers[0].combo1.addItemList (StromscoreProcessor::padPatternNames(), 1);
    layers[1].combo1.addItemList (StromscoreProcessor::bassPatternNames(), 1);
    layers[2].combo1.addItemList (StromscoreProcessor::arpFigureNames(), 1);
    layers[2].combo2.addItemList (StromscoreProcessor::arpRateNames(), 1);
    layers[2].combo2.setVisible (true);
    patternAttachment[0] = std::make_unique<APVTS::ComboBoxAttachment> (processor.apvts, "padPattern", layers[0].combo1);
    patternAttachment[1] = std::make_unique<APVTS::ComboBoxAttachment> (processor.apvts, "bassPattern", layers[1].combo1);
    patternAttachment[2] = std::make_unique<APVTS::ComboBoxAttachment> (processor.apvts, "arpFigure", layers[2].combo1);
    patternAttachment[3] = std::make_unique<APVTS::ComboBoxAttachment> (processor.apvts, "arpRate", layers[2].combo2);
    layers[0].combo1.setTooltip (u8 ("Muster der Fläche. Auto: wie es zur Wendung passt."));
    layers[1].combo1.setTooltip (u8 ("Muster des Basses. Auto: wie es zur Wendung passt, sehr ruhig gehalten, sehr aufgewühlt mindestens Achtel."));
    layers[2].combo1.setTooltip (u8 ("Figur des Arps. Auto: wie es zur Wendung passt."));
    layers[2].combo2.setTooltip (u8 ("Tempo des Arps. Auto: ruhig Viertel, mittel Achtel, aufgewühlt Sechzehntel."));
    for (auto& lv : layers) lv.resized();

    themeButton.onClick = [this]
    {
        theme = theme.dark ? lightTheme() : darkTheme();
        processor.uiTheme.store (theme.dark ? 0 : 1);
        processor.updateHostDisplay (juce::AudioProcessorListener::ChangeDetails{}.withNonParameterStateChanged (true));
        applyTheme();
    };
    content.addAndMakeVisible (themeButton);

    helpButton.setButtonText ("?");
    helpButton.setTooltip (u8 ("Hilfe: Einrichten und was machen die Regler?"));
    helpButton.onClick = [this] { helpScroll.setVisible (! helpScroll.isVisible()); };
    content.addAndMakeVisible (helpButton);

    helpScroll.setViewedComponent (&helpText, false);
    helpScroll.setScrollBarsShown (true, false);
    helpScroll.setVisible (false);
    content.addChildComponent (helpScroll);

    pad.setTooltip (u8 ("Stimmungsfeld: waagerecht die Färbung (dunkel bis hell), senkrecht die Intensität (ruhig bis aufgewühlt), Mausrad: Unruhe (Ring um den Punkt). Die fünf kleinen Lichter am Punkt zeigen, welche Ebenen gerade spielen. Automatisierbar, auch per CC."));
    changeBox.setTooltip (u8 ("Wann eine neue Wendung einsetzt, wenn du den Punkt deutlich bewegst: am nächsten Schlag, am nächsten Takt, alle 2 oder alle 4 Takte."));
    customButton.setTooltip (u8 ("An: deine eigene Akkordfolge statt der Wendungen. Die Akkorde bleiben fest, Figuren und Muster kommen von der Wendung, die am Punkt im Feld liegt."));
    editButton.setTooltip (u8 ("Eigene Akkordfolge bearbeiten: bis zu acht Akkorde mit Grundton, Art und Länge."));
    keyBox.setTooltip (u8 ("Grundton der Tonart."));
    meterBox.setTooltip (u8 ("Taktart: vom Projekt übernehmen oder fest einstellen. Ungerade Takte bekommen eigene Betonungen."));
    variation.setTooltip (u8 ("Sechzehn Kombinationen aus Wendungen und Figuren. Gleiche Nummer, gleiches Ergebnis."));
    swing.setTooltip (u8 ("Verschiebt die Zwischen-Achtel nach hinten, bis zum Triolen-Gefühl."));
    previewButton.setTooltip (u8 ("Einfacher Testklang im Plugin. Spielt auch ohne Wiedergabe mit eigener Uhr (nur der Testklang, kein MIDI)."));
    chordDisplay.setTooltip (u8 ("Der klingende Akkord, darunter die Wendung (acht Takte) oder deine eigene Folge und ihre Akkorde. Unten Färbung, Intensität und Unruhe: Die Balken lassen sich mit der Maus ziehen. Ab 80 % Unruhe, wo der Riss einsetzt, wird der Balken rot."));

    applyTheme();
    const int savedW = processor.uiWidth.load();
    const int restoredW = juce::jlimit (kBaseW / 2, kBaseW * 3, savedW);
    setSize (restoredW, juce::roundToInt ((float) restoredW * (float) kBaseH / (float) kBaseW));
    sizeReady = true;
    startTimerHz (30);
}

StromscoreEditor::~StromscoreEditor() { stopTimer(); setLookAndFeel (nullptr); }

void StromscoreEditor::updateCcButton()
{
    ccButton.setButtonText ("MIDI / CC");
    ccButton.setTooltip (u8 ("MIDI-Eingang: Färbung, Intensität, Unruhe. Ausgabe: Controller-Zuordnung und CC-Bereiche je Kanal."));
}

juce::TextButton& StromscoreEditor::rangeButtonFor (int r)
{
    return r == 5 ? layers[stromscore::kAkzent].rangeButton2 : layers[juce::jlimit (0, stromscore::kNumLayers - 1, r)].rangeButton;
}

void StromscoreEditor::showRangePanel (int r)
{
    auto panel = std::make_unique<RangePanel> (processor, r, theme.panel, theme.accent, theme.text, theme.dim);
    panel->setLookAndFeel (&look);
    auto& button = rangeButtonFor (r);
    juce::CallOutBox::launchAsynchronously (std::move (panel), content.getLocalArea (&button, button.getLocalBounds()), &content);
}

void StromscoreEditor::updateRangeButtons()
{
    for (int r = 0; r < stromscore::kNumRanges; ++r)
    {
        const juce::String n (r + 1);
        bool on = processor.apvts.getRawParameterValue ("umfang" + n)->load() >= 0.5f;
        int lo = juce::roundToInt (processor.apvts.getRawParameterValue ("tief" + n)->load());
        int hi = juce::roundToInt (processor.apvts.getRawParameterValue ("hoch" + n)->load());
        if (lo > hi) std::swap (lo, hi);
        const auto range = StromscoreProcessor::noteName (lo) + u8 ("–") + StromscoreProcessor::noteName (hi);
        juce::String text = on ? range : juce::String ("Umfang");
        if (r == 5)   // Stich: fest auf einer Taste oder Grundton des Akkords
        {
            const bool fixed = juce::roundToInt (processor.apvts.getRawParameterValue ("stichModus")->load()) == 0;
            if (fixed) { text = "Fest: " + StromscoreProcessor::noteName (juce::roundToInt (processor.apvts.getRawParameterValue ("stichTon")->load())); on = true; }
            else text = on ? "Akkord " + range : u8 ("Akkord · Umfang");
        }
        auto& b = rangeButtonFor (r);
        if (b.getButtonText() != text) b.setButtonText (text);
        if (b.getToggleState() != on) b.setToggleState (on, juce::dontSendNotification);
    }
}

void StromscoreEditor::updateMidiLabel()
{
    const int bars = processor.exportBars.load();
    midiDrag.label = "MIDI " + juce::String (bars);
    midiDrag.setTooltip (u8 ("Auf die DAW ziehen: neue Szene ab Takt 1, ") + juce::String (bars) + u8 (" Takte als MIDI-Datei mit den aktuellen Einstellungen, ohne frühere oder zukünftige Host-Automation. Eine Spur je Kanal; stumme Ebenen bleiben leer. Klick wechselt die Länge: 8, 16 oder 32 Takte."));
    midiDrag.repaint();
}

void StromscoreEditor::showOutputCcRanges (int channel) { showCcRanges (channel, ccButton); }

void StromscoreEditor::showCcRanges (int channel, juce::Component& anchor)
{
    auto panel = std::make_unique<CcRangePanel> (processor, channel);
    juce::CallOutBox::launchAsynchronously (std::move (panel), content.getLocalArea (&anchor, anchor.getLocalBounds()), &content);
}

void StromscoreEditor::showWendungInfo()
{
    const auto settings = processor.currentSettings();
    int genre = settings.genre;
    int index = processor.wendung.load();
    if (index < 0 || index >= stromscore::wendungCount (genre)) index = stromscore::Generator::pick (settings, 0);
    auto panel = std::make_unique<WendungInfoPanel> (genre, index, settings.key);
    juce::CallOutBox::launchAsynchronously (std::move (panel), infoButton.getBounds(), &content);
}

void StromscoreEditor::showCcMenu()
{
    static const int common[] = { 1, 2, 4, 7, 11, 16, 17, 18, 19, 21, 71, 72, 73, 74, 75, 76, 77 };
    const char* axis[3] = { "Färbung", "Intensität", "Unruhe" };
    juce::PopupMenu menu;
    for (int a = 0; a < 3; ++a)
    {
        juce::PopupMenu sub;
        const int now = processor.ccNumber[a].load();
        sub.addItem (1000 * (a + 1), "aus", true, now == 0);
        for (int cc : common)
            sub.addItem (1000 * (a + 1) + cc, "CC " + juce::String (cc), true, now == cc);
        menu.addSubMenu (u8 (axis[a]) + " (" + (now > 0 ? "CC " + juce::String (now) : juce::String ("aus")) + ")", sub);
    }
    menu.addSeparator();
    menu.addItem (9999, u8 ("Vorgabe: 11 · 1 · 74"));
    menu.addSeparator();
    menu.addSectionHeader (u8 ("Ausgabe an die Spuren"));
    const bool dyn = processor.apvts.getRawParameterValue ("dynamikCc")->load() >= 0.5f;
    menu.addItem (8001, u8 ("CC-Ausgabe für alle Kanäle"), true, dyn);
    menu.addItem (8002, u8 ("Ausgang: CC-Bereiche …"));
    const char* outName[2] = { "Dynamik", "Ausdruck" };
    static const int outCommon[] = { 1, 2, 7, 11, 21 };
    for (int o = 0; o < 2; ++o)
    {
        juce::PopupMenu sub;
        const int now = processor.ccOut[o].load();
        sub.addItem (5000 + 1000 * o, "aus", true, now == 0);
        for (int cc : outCommon) sub.addItem (5000 + 1000 * o + cc, "CC " + juce::String (cc), true, now == cc);
        menu.addSubMenu (u8 (outName[o]) + " (" + (now > 0 ? "CC " + juce::String (now) : juce::String ("aus")) + ")", sub, dyn);
    }
    menu.showMenuAsync (juce::PopupMenu::Options().withTargetComponent (&ccButton), [safe = juce::Component::SafePointer<StromscoreEditor> (this)] (int r)
    {
        if (safe == nullptr) return;
        auto& processor = safe->processor;
        if (r == 0) return;
        if (r == 9999) { processor.ccNumber[0].store (11); processor.ccNumber[1].store (1); processor.ccNumber[2].store (74); }
        else if (r == 8002) { safe->showOutputCcRanges(); return; }
        else if (r == 8001)
        {
            auto* p = processor.apvts.getParameter ("dynamikCc");
            p->beginChangeGesture(); p->setValueNotifyingHost (p->getValue() >= 0.5f ? 0.0f : 1.0f); p->endChangeGesture();
        }
        else if (r >= 5000 && r < 7000) processor.ccOut[(r - 5000) / 1000].store ((r - 5000) % 1000);
        else { const int a = r / 1000 - 1; if (a >= 0 && a < 3) processor.ccNumber[a].store (r % 1000); }
        processor.updateHostDisplay (juce::AudioProcessorListener::ChangeDetails{}.withNonParameterStateChanged (true));
        safe->updateCcButton();
    });
}

void StromscoreEditor::timerCallback()
{
    const bool wantsDark = processor.uiTheme.load() != 1;
    if (theme.dark != wantsDark) { theme = wantsDark ? darkTheme() : lightTheme(); applyTheme(); }
    const int width = processor.uiWidth.load();
    if (getWidth() != width) setSize (width, juce::roundToInt ((float) width * kBaseH / kBaseW));

    // Akkord-Anzeige
    const int w = processor.wendung.load();
    const int key = juce::roundToInt (processor.apvts.getRawParameterValue ("key")->load());
    const int gen = processor.genreInUse.load();
    chordDisplay.playing = w >= 0 && (w == stromscore::kCustomWendung || w < stromscore::wendungCount (gen));
    chordDisplay.meter = u8 ("Takt ") + juce::String (processor.meterNum.load()) + "/" + juce::String (processor.meterDen.load());
    const auto settings = processor.currentSettings();
    {
        int total = 0;
        for (const auto& c : settings.customChords) total += c.bars;
        slots.totalText = total > 0 ? u8 ("Länge der Folge: ") + juce::String (total) + (total == 1 ? " Takt" : " Takte")
                                    : u8 ("Alle Plätze leer: es spielt der Grundakkord der Tonart.");
        if (slots.isVisible()) slots.repaint();
    }
    if (chordDisplay.playing)
    {
        const auto custom = stromscore::customWendung (settings);
        const auto& wd = w == stromscore::kCustomWendung ? custom : stromscore::wendungAt (gen, w);
        char buf[32];
        stromscore::chordName (key, processor.chordRoot.load(), processor.chordType.load(), buf, (int) sizeof (buf));
        chordDisplay.chord = juce::String (juce::CharPointer_UTF8 (buf));
        chordDisplay.wendung = juce::String (juce::CharPointer_UTF8 (wd.name));
        chordDisplay.custom = w == stromscore::kCustomWendung;
        const int st = processor.styleIndex.load();
        if (chordDisplay.custom && st >= 0 && st < stromscore::wendungCount (gen))
            chordDisplay.wendung << u8 (" · Stil: ") << juce::String (juce::CharPointer_UTF8 (stromscore::wendungAt (gen, st).name));
        stromscore::chordName (key, processor.nextRoot.load(), processor.nextType.load(), buf, (int) sizeof (buf));
        chordDisplay.nextChord = juce::String (juce::CharPointer_UTF8 (buf));
        chordDisplay.progress = processor.chordProgress.load();
        chordDisplay.numChips = wd.n;
        for (int i = 0; i < wd.n; ++i)
        {
            stromscore::chordName (key, wd.ch[i].root, wd.ch[i].type, buf, (int) sizeof (buf));
            chordDisplay.chips[i] = juce::String (juce::CharPointer_UTF8 (buf));
            if (wd.ch[i].bass >= 0)
            {
                stromscore::chordName (key, wd.ch[i].bass, stromscore::Maj, buf, (int) sizeof (buf));
                chordDisplay.chips[i] << "/" << juce::String (juce::CharPointer_UTF8 (buf));
            }
        }
        chordDisplay.current = processor.chordIndex.load();
    }
    {
        const bool drive = settings.drive;
        const bool running = processor.sceneBar.load() >= 0;
        const bool showNow = drive && running;
        pad.targetPending = processor.targetSet.load();
        const bool visible = drive || pad.targetPending;
        if (pad.showB != visible || pad.showNow != showNow) { pad.showB = visible; pad.showNow = showNow; pad.repaint(); }
        if (showNow && (pad.nowX != processor.pointX.load() || pad.nowY != processor.pointY.load()))
        {
            pad.nowX = processor.pointX.load(); pad.nowY = processor.pointY.load();
            pad.repaint();
        }
        chordDisplay.mood[0] = showNow ? pad.nowX : pad.x;
        chordDisplay.mood[1] = showNow ? pad.nowY : pad.y;
    }
    chordDisplay.mood[2] = pad.z;
    updateSceneStatus();
    chordDisplay.repaint();

    // Kandidaten an der aktuellen Stelle
    {
        int c[6];
        const int n = stromscore::Generator::candidates (settings, c, 6);
        juce::String t;
        for (int i = 0; i < n; ++i) t << (i > 0 ? u8 (" · ") : juce::String()) << juce::String (juce::CharPointer_UTF8 (stromscore::wendungAt (settings.genre, c[i]).name));
        chordDisplay.candidates = t;
    }

    // Ebenen
    updateRangeButtons();
    const auto& s = settings;
    static const int firstOut[stromscore::kNumLayers] = { stromscore::OutPadLong, stromscore::OutBassLong, stromscore::OutArp, stromscore::OutTupfer, stromscore::OutCounter };
    for (int i = 0; i < stromscore::kNumLayers; ++i)
    {
        auto& lv = layers[i];
        for (int c = 0; c < lv.numLamps; ++c)
        {
            const float a = processor.activity[firstOut[i] + c].exchange (0.0f);
            lv.activity[c] = std::max (a, lv.activity[c] * 0.88f);
        }
        lv.active = stromscore::Generator::layerActive (s, i);
        bool anySolo = false;
        for (bool b : s.solo) anySolo = anySolo || b;
        juce::String entry;
        if (anySolo ? ! s.solo[i] : s.mute[i]) entry = "stumm";
        else
        {
            const float t = stromscore::kLayerStart[i] - s.layerIntensity[i];
            auto pct = [] (float v) { return v <= 0.0f ? juce::String ("immer") : juce::String (juce::roundToInt (v * 100.0f)) + " %"; };
            entry = t <= 0.0f ? juce::String ("immer") : t > 1.0f ? (i == stromscore::kAkzent ? juce::String ("bei Unruhe") : juce::String ("nie"))
                                                                   : "ab " + pct (t);
            if (i == stromscore::kAkzent && t <= 1.0f)   // Akzent: Tupfer und Stich setzen getrennt ein
            {
                const float ts = stromscore::kStichStart - s.layerIntensity[i];
                entry = (t <= 0.0f ? juce::String ("immer") : "ab " + juce::String (juce::roundToInt (t * 100.0f)))
                      + " / " + (ts > 1.0f ? juce::String ("nie") : ts <= 0.0f ? juce::String ("immer") : juce::String (juce::roundToInt (ts * 100.0f)) + " %");
            }
        }
        if (lv.entry != entry) { lv.entry = entry; lv.intensity.updateText(); }
        lv.repaint();
    }
    pad.repaint();   // der Unruhe-Ring zappelt
}

void StromscoreEditor::updateSceneStatus()
{
    const auto s = processor.currentSettings();
    const int bar = processor.sceneBar.load();
    const auto names = StromscoreProcessor::entryNames();
    juce::String t;
    if (bar < 0)
    {
        t = u8 ("Die Szene beginnt mit dem Start der Wiedergabe");
        if (s.drive) t << u8 (" · rechts Ziel B setzen");
    }
    else if (processor.sceneOver.load()) t = u8 ("Szene zu Ende (Takt ") + juce::String (s.sceneBars) + u8 (") · neu mit dem nächsten Start");
    else
    {
        t = "Takt " + juce::String (bar + 1);
        const int e = juce::jlimit (1, stromscore::kNumEntries - 1, processor.sceneEntry.load());
        if (s.scene || s.sceneBars > 0) t << u8 (" · ") << names[e] << (s.entry == stromscore::EntryAuto ? " (Auto)" : "");
        if (s.scene && e != stromscore::EntryAll && bar < s.buildBars) t << u8 (" · Aufbau bis Takt ") << s.buildBars;
        if (s.sceneBars > 0) t << u8 (" · noch ") << (s.sceneBars - bar) << ((s.sceneBars - bar) == 1 ? " Takt" : " Takte");
    }
    if (s.drive)
    {
        const float progress = processor.driveProgress.load();
        if (bar < 0) t << u8 (" · Fahrt bereit");
        else if (processor.publishedDriveGeneration.load() != processor.driveGeneration.load() || progress < 0)
        {
            const int from = processor.driveFromLive.load();
            t << u8 (" · Fahrt wartet");
            if (processor.publishedDriveGeneration.load() == processor.driveGeneration.load())
                t << u8 (" auf Takt ") << ((from >= 0 ? from : s.driveFrom) + 1);
            else t << u8 (" auf nächsten Takt");
        }
        else t << (s.driveCurve == stromscore::CurveWave && progress > 0.5f ? u8 (" · Rückfahrt ") : u8 (" · Fahrt läuft "))
               << juce::roundToInt (100.0f * juce::jlimit (0.0f, 1.0f, progress)) << " %";
    }
    else
    {
        switch (processor.driveOutcome.load())
        {
            case 1: t << u8 (" · Fahrt angekommen bei B"); break;
            case 2: t << u8 (" · Fahrt zurück bei A"); break;
            case 3: t << u8 (" · Manuell übernommen"); break;
            case 4: t << u8 (" · Fahrt angehalten"); break;
            default: if (processor.targetSet.load()) t << u8 (" · Ziel B bereit"); break;
        }
    }
    if (sceneStatus.getText() != t) sceneStatus.setText (t, juce::dontSendNotification);
    const bool drive = s.drive;
    for (auto* c : std::initializer_list<juce::Component*> { &startBox, &durBox, &curveBox, &startLabel, &durLabel, &curveLabel }) c->setEnabled (drive);
    endBox.setEnabled (s.sceneBars > 0); endLabel.setEnabled (s.sceneBars > 0);
    buildBox.setEnabled (s.scene);
}

void StromscoreEditor::applyTheme()
{
    look.setColour (juce::Slider::thumbColourId, theme.accent);
    look.setColour (juce::Slider::rotarySliderFillColourId, theme.accent);
    look.setColour (juce::Slider::rotarySliderOutlineColourId, theme.line);
    look.setColour (juce::Slider::trackColourId, theme.accent.withAlpha (0.75f));
    look.setColour (juce::Slider::backgroundColourId, theme.line);
    look.setColour (juce::Slider::textBoxTextColourId, theme.text);
    look.setColour (juce::Slider::textBoxOutlineColourId, juce::Colours::transparentBlack);
    look.setColour (juce::ComboBox::backgroundColourId, theme.bg);
    look.setColour (juce::ComboBox::textColourId, theme.text);
    look.setColour (juce::ComboBox::arrowColourId, theme.text);
    look.setColour (juce::ComboBox::outlineColourId, theme.line);
    look.setColour (juce::PopupMenu::backgroundColourId, theme.panel);
    look.setColour (juce::PopupMenu::textColourId, theme.text);
    look.setColour (juce::PopupMenu::highlightedBackgroundColourId, theme.accent);
    look.setColour (juce::PopupMenu::highlightedTextColourId, juce::Colours::black);
    look.setColour (juce::Label::textColourId, theme.text);
    look.setColour (juce::TextButton::buttonColourId, theme.dark ? theme.panel : theme.bg);
    look.setColour (juce::TextButton::buttonOnColourId, theme.accent);
    look.setColour (juce::TextButton::textColourOffId, theme.text);
    look.setColour (juce::TextButton::textColourOnId, juce::Colours::black);
    look.setColour (juce::TooltipWindow::backgroundColourId, theme.dark ? theme.panel.brighter (0.15f) : juce::Colours::white);
    look.setColour (juce::TooltipWindow::textColourId, theme.text);
    look.setColour (juce::TooltipWindow::outlineColourId, theme.accent.withAlpha (0.6f));

    for (auto* l : { &padLabel, &varietyLabel, &keyLabel, &meterLabel, &variationLabel, &swingLabel, &chordLabel, &changeLabel, &customLabel,
                     &sceneLabel, &driveLabel, &entryLabel, &lengthLabel, &endLabel, &startLabel, &durLabel, &curveLabel })
        l->setColour (juce::Label::textColourId, theme.dim);
    sceneStatus.setColour (juce::Label::textColourId, theme.text);
    sceneLabel.setFont (juce::FontOptions (12.0f, juce::Font::bold)); driveLabel.setFont (juce::FontOptions (12.0f, juce::Font::bold));
    const auto inner = theme.dark ? theme.bg : theme.bg.brighter (0.05f);
    pad.panel = inner; pad.line = theme.line; pad.accent = theme.accent; pad.text = theme.text; pad.dim = theme.dim;
    chordDisplay.panel = inner; chordDisplay.line = theme.line; chordDisplay.accent = theme.accent; chordDisplay.text = theme.text; chordDisplay.dim = theme.dim;
    midiDrag.panel = theme.panel; midiDrag.line = theme.line; midiDrag.accent = theme.accent; midiDrag.text = theme.text; midiDrag.dim = theme.dim;
    slots.panel = theme.panel; slots.line = theme.line; slots.accent = theme.accent; slots.text = theme.text; slots.dim = theme.dim;
    for (auto& l : layers) { l.panel = theme.panel; l.line = theme.line; l.accent = theme.accent; l.text = theme.text; l.dim = theme.dim; }
    themeButton.setButtonText (theme.dark ? "Look: Dunkel" : "Look: Hell");
    helpText.setAttributed (buildHelp (theme.text, theme.accent, theme.dim));
    helpScroll.fill = theme.panel;
    helpScroll.edge = theme.line;
    sendLookAndFeelChange();
    repaint();
}

float StromscoreEditor::subtitleEnd() const
{
    juce::GlyphArrangement ga;
    ga.addLineOfText (juce::Font (juce::FontOptions (12.0f, juce::Font::bold)), u8 ("AUDIO DRAMA UNDERSCORE INSPIRATOR"), 0.0f, 0.0f);
    return kSubtitleX + ga.getBoundingBox (0, -1, true).getWidth();
}

void StromscoreEditor::paint (juce::Graphics& g)
{
    g.fillAll (theme.bg);
    g.addTransform (juce::AffineTransform::scale (uiScale));
    const int W = kBaseW;

    g.setColour (theme.panel);
    g.fillRect (0, 0, W, 64);
    g.setColour (theme.line);
    g.fillRect (0, 63, W, 1);
    g.setColour (theme.accent);
    g.fillRect (0, 0, 5, 64);

    if (logo.isValid())
    {
        g.setColour (theme.text);
        g.drawImage (logo, juce::Rectangle<float> (14.0f, 4.0f, 56.0f, 56.0f), juce::RectanglePlacement::centred, true);
    }

    const float subX = kSubtitleX;
    g.setColour (theme.text);
    g.setFont (juce::FontOptions (24.0f, juce::Font::bold));
    g.drawText ("STROMSCORE", 80, 8, 210, 30, juce::Justification::centredLeft);
    g.setColour (theme.accent);
    g.setFont (juce::FontOptions (12.0f, juce::Font::bold));
    const juce::String subtitle = u8 ("AUDIO DRAMA UNDERSCORE INSPIRATOR");
    g.drawText (subtitle, (int) subX, 15, 320, 22, juce::Justification::centredLeft);
    g.setColour (theme.dim);
    g.setFont (juce::FontOptions (11.0f));
    g.drawText (juce::String (juce::CharPointer_UTF8 ("STROMSCHLAG AUDIO  \xc2\xb7  v" PLUGIN_VERSION_TEXT)), 80, 36, 300, 16, juce::Justification::centredLeft);

    // Symbol: Violinschluessel, Notenlinien, drei Noten mit p und f (kompakt direkt hinter dem Untertitel, folgt dem Look)
    {
        const float x0 = subtitleEnd() + 12.0f, x1 = x0 + kSymbolW, y0 = 22.0f, gap = 4.0f;
        g.setColour (theme.panel.interpolatedWith (theme.text, 0.34f));
        for (int i = 0; i < 5; ++i)
            g.fillRect (x0, y0 + (float) i * gap, x1 - x0, 1.0f);

        juce::Path clef;
        clef.startNewSubPath (10.0f, 34.0f);
        clef.cubicTo (10.0f, 38.0f, 16.0f, 38.0f, 16.0f, 34.0f);
        clef.cubicTo (16.0f, 28.0f, 14.0f, 10.0f, 14.0f, 5.0f);
        clef.cubicTo (14.0f, 0.0f, 19.0f, 0.0f, 18.0f, 6.0f);
        clef.cubicTo (17.0f, 14.0f, 9.0f, 17.0f, 9.0f, 22.0f);
        clef.cubicTo (9.0f, 28.0f, 19.0f, 28.0f, 19.0f, 22.0f);
        clef.cubicTo (19.0f, 17.0f, 11.0f, 16.0f, 11.0f, 21.0f);
        g.strokePath (clef, juce::PathStrokeType (1.2f, juce::PathStrokeType::curved, juce::PathStrokeType::rounded),
                      juce::AffineTransform::translation (-9.0f, -1.0f).scaled (0.9f).translated (x0 + 2.0f, y0 - 8.0f));

        const float notes[][2] = { { 28, 1 }, { 40, 4 }, { 52, 3 } };
        for (const auto& n : notes)
        {
            const float cx = x0 + n[0];
            const float cy = y0 + 4.0f * gap - n[1] * gap * 0.5f;
            juce::Path head;
            head.addEllipse (-2.6f, -1.9f, 5.2f, 3.8f);
            g.fillPath (head, juce::AffineTransform::rotation (-0.4f).translated (cx, cy));
            g.fillRect (cx + 2.0f, cy - 10.0f, 1.0f, 10.0f);
        }
        g.setFont (juce::Font (juce::FontOptions ("Times New Roman", 13.0f, juce::Font::bold | juce::Font::italic)));
        g.drawText ("p", (int) (x0 + 21.0f), (int) (y0 + 18.0f), 12, 16, juce::Justification::centred);
        g.drawText ("f", (int) (x0 + 49.0f), (int) (y0 + 18.0f), 12, 16, juce::Justification::centred);
    }

    // Obere Karte
    g.setColour (theme.panel);
    g.fillRoundedRectangle (12.0f, 76.0f, (float) W - 24.0f, 244.0f, 8.0f);
    g.setColour (theme.line);
    g.drawRoundedRectangle (12.5f, 76.5f, (float) W - 25.0f, 243.0f, 8.0f, 1.0f);
    for (float x : { 244.0f, 410.0f, 586.0f })
        g.fillRect (x, 88.0f, 1.0f, 220.0f);

    // Szene und Fahrt
    g.setColour (theme.panel);
    g.fillRoundedRectangle (12.0f, 330.0f, (float) W - 24.0f, 84.0f, 8.0f);
    g.setColour (theme.line);
    g.drawRoundedRectangle (12.5f, 330.5f, (float) W - 25.0f, 83.0f, 8.0f, 1.0f);
    g.fillRect (24.0f, 371.5f, (float) W - 48.0f, 1.0f);
}

void StromscoreEditor::resized()
{
    if (sizeReady)
        processor.uiWidth.store (getWidth());
    uiScale = std::min ((float) getWidth() / kBaseW, (float) getHeight() / kBaseH);
    content.setTransform (juce::AffineTransform::scale (uiScale));
    content.setBounds (0, 0, kBaseW, kBaseH);
    repaint();

    const int w = kBaseW;
    // Kopfzeile: CC-Knopf klein links neben dem Look-Schalter
    helpButton.setBounds (w - 44, 18, 30, 28);
    themeButton.setBounds (w - 150, 18, 100, 28);
    const int ccX = std::max (juce::roundToInt (subtitleEnd() + 12.0f + kSymbolW + 14.0f), w - 150 - 8 - 150);
    ccButton.setBounds (ccX, 18, w - 150 - 8 - ccX, 28);
    helpScroll.setBounds (12, 76, w - 24, kBaseH - 88);
    helpText.setWidth (helpScroll.getMaximumVisibleWidth());

    // Stimmungsfeld, darunter Unruhe
    padLabel.setBounds (24, 82, 90, 18);
    genreScore.setBounds (118, 80, 52, 20);
    genrePop.setBounds (172, 80, 60, 20);
    pad.setBounds (24, 102, 208, 208);

    // Tonart, Takt, Variation, Swing
    keyLabel.setBounds (256, 82, 140, 18);
    keyBox.setBounds (256, 102, 142, 26);
    meterLabel.setBounds (256, 136, 140, 18);
    meterBox.setBounds (256, 156, 142, 26);
    variationLabel.setBounds (256, 190, 140, 18);
    variation.setBounds (256, 210, 142, 26);
    swingLabel.setBounds (256, 244, 140, 18);
    swing.setBounds (252, 264, 150, 24);

    // Wechsel, eigene Folge, Vorhoeren
    changeLabel.setBounds (422, 82, 150, 18);
    changeBox.setBounds (422, 102, 152, 26);
    customLabel.setBounds (422, 136, 150, 18);
    customButton.setBounds (422, 156, 116, 26);
    editButton.setBounds (542, 156, 32, 26);
    passingButton.setBounds (422, 188, 152, 26);
    varietyLabel.setBounds (422, 222, 150, 18);
    variety.setBounds (418, 240, 160, 24);
    previewButton.setBounds (422, 280, 94, 26);
    midiDrag.setBounds (520, 280, 54, 26);

    // Akkord-Anzeige
    chordLabel.setBounds (598, 82, 200, 18);
    infoButton.setBounds (w - 150, 78, 126, 22);
    chordDisplay.setBounds (598, 102, w - 622, 208);
    slots.setBounds (12, 76, w - 24, 244);

    // Szene (obere Zeile) und Fahrt (untere Zeile)
    {
        const int y1 = 340, y2 = 381, h = 24;
        sceneLabel.setBounds (22, y1, 58, h);
        sceneButton.setBounds (80, y1, 70, h);
        buildBox.setBounds (154, y1, 84, h);
        entryLabel.setBounds (248, y1, 56, h);
        entryBox.setBounds (302, y1, 146, h);
        diceButton.setBounds (452, y1, 86, h);
        hardness.setBounds (548, y1, 132, h);
        lengthLabel.setBounds (690, y1, 42, h);
        lengthBox.setBounds (730, y1, 98, h);
        endLabel.setBounds (838, y1, 36, h);
        endBox.setBounds (872, y1, 104, h);
        driveLabel.setBounds (22, y2, 58, h);
        driveButton.setBounds (80, y2, 70, h);
        startLabel.setBounds (160, y2, 40, h);
        startBox.setBounds (198, y2, 98, h);
        durLabel.setBounds (306, y2, 42, h);
        durBox.setBounds (346, y2, 90, h);
        curveLabel.setBounds (446, y2, 42, h);
        curveBox.setBounds (486, y2, 132, h);
        sceneStatus.setBounds (630, y2, w - 24 - 630, h);
    }

    // Ebenen
    for (int i = 0; i < stromscore::kNumLayers; ++i)
        layers[i].setBounds (12 + i * 197, 424, 188, kBaseH - 436);
    if (slots.isVisible()) slots.toFront (false);
    helpScroll.toFront (false);
}
