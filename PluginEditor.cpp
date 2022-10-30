/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
SynthAudioProcessorEditor::SynthAudioProcessorEditor(SynthAudioProcessor& p)
    : AudioProcessorEditor(&p)
    , audioProcessor(p)
    , osc(audioProcessor.apvts, "OSC1WAVETYPE", "OSC1FMFREQ", "OSC1FMDEPTH", "OSC1DETUNE")
    , adsr("Amp Envelope", audioProcessor.apvts, "ATTACK", "DECAY", "SUSTAIN", "RELEASE")
    , filter(audioProcessor.apvts, "FILTERTYPE", "FILTERCUTOFF", "FILTERRES")
    , modAdsr("Mod Envelope", audioProcessor.apvts, "MODATTACK", "MODDECAY", "MODSUSTAIN", "MODRELEASE")
    , reverb(audioProcessor.apvts, "REVERBROOM", "REVERBDAMP", "REVERBWET", "REVERBDRY", "REVERBWIDTH", "REVERBFREEZE")
    , gain(audioProcessor.apvts, "GAIN")
    , chorus(audioProcessor.apvts, "CHORUSRATE", "CHORUSDEPTH", "CHORUSDELAY", "CHORUSFEEDBACK", "CHORUSMIX")
{
    setSize(1000, 580);




    getLookAndFeel().setColour(juce::Slider::trackColourId, fillSliderRot);
    getLookAndFeel().setColour(juce::Slider::backgroundColourId, backgroundSlider);

    getLookAndFeel().setColour(juce::Slider::rotarySliderOutlineColourId, backgroundSlider);
    getLookAndFeel().setColour(juce::Slider::rotarySliderFillColourId, fillSliderRot);

    getLookAndFeel().setColour(juce::Slider::thumbColourId, thumbSlider);

    addAndMakeVisible(adsr);
    addAndMakeVisible(osc);
    addAndMakeVisible(filter);
    addAndMakeVisible(modAdsr);
    addAndMakeVisible(reverb);
    addAndMakeVisible(chorus);
    addAndMakeVisible(gain);
}

SynthAudioProcessorEditor::~SynthAudioProcessorEditor()
{
}

//==============================================================================
void SynthAudioProcessorEditor::paint (juce::Graphics& g) 
{
    // PAZI SE OVOG -> MOZES NAPRAVIT COMPONENT ALI SI BOUNDS STAVIO PREMALE
    // NPR ZA CIJELI OSC JE 30 A TI SI ZA COMPONENT STAVIO 50 -> NISTA SE NECE NACRTAT IAKO SI SVE DOBRO NAPRAVIO CODEWISE
    g.fillAll(background);

}

void SynthAudioProcessorEditor::resized()
{
    const auto paddingX = 5;
    const auto paddingY = 10;
    const auto paddingY2 = 210;
    const auto paddingY3 = 410;
    const auto paddingY4 = 610;

    const auto width = 300;
    const auto height = 200;

    osc.setBounds(paddingX, paddingY, width * 1.4f, height);
    adsr.setBounds(osc.getRight() + 30, paddingY, width + 100, height);
    filter.setBounds(paddingX, paddingY2, width * 1.4, height);
    modAdsr.setBounds(filter.getRight() + 30, paddingY2, width + 225, height);
    reverb.setBounds(paddingX, paddingY3, width * 1.4f, height * 0.8f);
    chorus.setBounds(reverb.getRight() + 30, paddingY3, width * 1.75f, height * 0.8f);
    gain.setBounds(adsr.getRight() + 30, paddingY, width / 3, height);
}