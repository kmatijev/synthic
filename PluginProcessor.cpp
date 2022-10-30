/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "Data/GainData.h"

//==============================================================================
SynthAudioProcessor::SynthAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
    : AudioProcessor(BusesProperties()
#if ! JucePlugin_IsMidiEffect
#if ! JucePlugin_IsSynth
        .withInput("Input", juce::AudioChannelSet::stereo(), true)
#endif
        .withOutput("Output", juce::AudioChannelSet::stereo(), true)
#endif
    ), apvts(*this, nullptr, "Parameters", createParameters())
#endif
{
 
    for (auto midiChannel = 0; midiChannel < maxMidiChannels; midiChannel++)
    {
        for (auto i = 0; i < maxNumberOfVoices; ++i)
        {
            synth.addSound(new SynthSound());
            synth.addVoice(new SynthVoice());
        }
    }
    //for (int i = 0; i < 8; i++)
    //{
    //    synth.addSound(new SynthSound());
    //    synth.addVoice(new SynthVoice());
    //}

}

SynthAudioProcessor::~SynthAudioProcessor()
{
}

//==============================================================================
const juce::String SynthAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool SynthAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool SynthAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool SynthAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double SynthAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int SynthAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int SynthAudioProcessor::getCurrentProgram()
{
    return 0;
}

void SynthAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String SynthAudioProcessor::getProgramName (int index)
{
    return {};
}

void SynthAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void SynthAudioProcessor::prepareToPlay(double sampleRate, int samplesPerBlock)
{
    
    synth.setCurrentPlaybackSampleRate(sampleRate);

    for (int i = 0; i < synth.getNumVoices(); i++)
    {
        if (auto voice = dynamic_cast<SynthVoice*>(synth.getVoice(i)))
        {
            voice->prepareToPlay(sampleRate, samplesPerBlock, getTotalNumOutputChannels());
        }
    }
}

void SynthAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool SynthAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void SynthAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();


    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    for (int i = 0; i < synth.getNumVoices(); ++i)
    {
        if (auto voice = dynamic_cast<SynthVoice*>(synth.getVoice(i)))
        {


            // AMP ADSR
            auto& attack = *apvts.getRawParameterValue("ATTACK");
            auto& decay = *apvts.getRawParameterValue("DECAY");
            auto& sustain = *apvts.getRawParameterValue("SUSTAIN");
            auto& release = *apvts.getRawParameterValue("RELEASE");

            // FILTER
            auto& filterType = *apvts.getRawParameterValue("FILTERTYPE");
            auto& cutoff = *apvts.getRawParameterValue("FILTERCUTOFF");
            auto& resonance = *apvts.getRawParameterValue("FILTERRES");

            // MOD ADSR
            auto& modAttack = *apvts.getRawParameterValue("MODATTACK");
            auto& modDecay = *apvts.getRawParameterValue("MODDECAY");
            auto& modSustain = *apvts.getRawParameterValue("MODSUSTAIN");
            auto& modRelease = *apvts.getRawParameterValue("MODRELEASE");

            auto& oscWaveChoice = *apvts.getRawParameterValue("OSC1WAVETYPE");

            auto& fmDepth = *apvts.getRawParameterValue("OSC1FMDEPTH");
            auto& fmFreq = *apvts.getRawParameterValue("OSC1FMFREQ");

            auto& detune = *apvts.getRawParameterValue("OSC1DETUNE");

            // REVERB
            auto& revRoom = *apvts.getRawParameterValue("REVERBROOM");
            auto& revDamp = *apvts.getRawParameterValue("REVERBDAMP");
            auto& revWet = *apvts.getRawParameterValue("REVERBWET");
            auto& revDry = *apvts.getRawParameterValue("REVERBDRY");
            auto& revWidth = *apvts.getRawParameterValue("REVERBWIDTH");
            //auto& revFreeze = *apvts.getRawParameterValue("REVERBFREEZE");
            
            // CHORUS
            auto& chorusRate = *apvts.getRawParameterValue("CHORUSRATE");
            auto& chorusDepth = *apvts.getRawParameterValue("CHORUSDEPTH");
            auto& chorusDelay = *apvts.getRawParameterValue("CHORUSDELAY");
            auto& chorusFeedback = *apvts.getRawParameterValue("CHORUSFEEDBACK");
            auto& chorusMix = *apvts.getRawParameterValue("CHORUSMIX");

            // GAIN
            auto& gainLin = *apvts.getRawParameterValue("GAIN");

            voice->getOscillator().setWaveType(oscWaveChoice);
            voice->getOscillator().setFmParams(fmDepth, fmFreq, detune);
            voice->updateAdsr(attack.load(), decay.load(), sustain.load(), release.load()); // zbog atomic floata, takes a lot more power to update
            voice->updateFilter(filterType.load(), cutoff.load(), resonance.load());
            voice->updateModAdsr(modAttack, modDecay, modSustain, modRelease);
            voice->updateReverb(revRoom, revDamp, revWet, revDry, revWidth, 0.0f);
            voice->updateChorus(chorusRate, chorusDepth, chorusDelay, chorusFeedback, chorusMix);
            voice->updateGain(gainLin);
        }
    }

    //updateReverbSettings();

    //juce::dsp::AudioBlock<float> block(buffer);
    //juce::dsp::ProcessContextReplacing<float> ctx(block);
    //reverb.process(ctx);
    synth.renderNextBlock(buffer, midiMessages, 0, buffer.getNumSamples());
}

//void SynthAudioProcessor::updateReverbSettings()
//{
//    params.roomSize = apvts.getParameter("REVERBROOM")->getValue();
//    params.damping = apvts.getParameter("REVERBDAMP")->getValue();
//    params.width = apvts.getParameter("REVERBWIDTH")->getValue();
//    params.wetLevel = apvts.getParameter("REVERBWET")->getValue();
//    params.dryLevel = 1.0f - apvts.getParameter("REVERBDRY")->getValue();
//    params.freezeMode = apvts.getParameter("REVERBFREEZE")->getValue();
//
//    reverb.setParameters(params);
//}

//==============================================================================
bool SynthAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* SynthAudioProcessor::createEditor()
{
    return new SynthAudioProcessorEditor (*this);
}

//==============================================================================
void SynthAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    auto state = apvts.copyState();
    std::unique_ptr<juce::XmlElement> xml(state.createXml());
    copyXmlToBinary(*xml, destData);
}

void SynthAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    std::unique_ptr<juce::XmlElement> xmlState(getXmlFromBinary(data, sizeInBytes));

    if (xmlState.get() != nullptr)
        if (xmlState->hasTagName(apvts.state.getType()))
            apvts.replaceState(juce::ValueTree::fromXml(*xmlState));
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new SynthAudioProcessor();
}

// Value Tree 
juce::AudioProcessorValueTreeState::ParameterLayout SynthAudioProcessor::createParameters()
{

    std::vector<std::unique_ptr<juce::RangedAudioParameter>> params;
    
    // OSC SELECT
    params.push_back(std::make_unique<juce::AudioParameterChoice>("OSC1WAVETYPE", "Osc 1 Wave Type",
        juce::StringArray{ "Sine", "Saw", "Square" }, 0));

    // FM
    params.push_back(std::make_unique<juce::AudioParameterFloat>("OSC1FMFREQ", "Osc 1 FM Frequency", 
        juce::NormalisableRange<float> { 0.0f, 1000.0f, 1, 0.3f }, 0.0f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("OSC1FMDEPTH", "Osc 1 FM Depth", 
        juce::NormalisableRange<float> { 0.0f, 1000.0f, 0.001f, 0.3f }, 0.0f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("OSC1DETUNE", "Detune",
        juce::NormalisableRange<float> { 0.0f, 100.0f, 0.001f, 0.3f}, 0.0f));

    // ADSR
    params.push_back(std::make_unique<juce::AudioParameterFloat>("ATTACK", "Attack", 
        juce::NormalisableRange<float> { 0.0f, 1.0f, 0.001f, 0.3f }, 0.1f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("DECAY", "Decay", 
        juce::NormalisableRange<float> { 0.0f, 1.0f, 0.001f, 0.3f }, 0.3f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("SUSTAIN", "Sustain", 
        juce::NormalisableRange<float> { 0.0f, 1.0f, 0.001f }, 1.0f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("RELEASE", "Release", 
        juce::NormalisableRange<float> { 0.0f, 3.0f, 0.001f, 0.3f }, 0.2f));

    // Filter ADSR
    params.push_back(std::make_unique<juce::AudioParameterFloat>("MODATTACK", "Mod Attack",
        juce::NormalisableRange<float> { 0.0f, 1.0f, 0.001f, 0.3f }, 0.1f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("MODDECAY", "Mod Decay",
        juce::NormalisableRange<float> { 0.0f, 1.0f, 0.001f, 0.3f }, 0.3f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("MODSUSTAIN", "Mod Sustain",
        juce::NormalisableRange<float> { 0.0f, 1.0f, 0.001f }, 1.0f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("MODRELEASE", "Mod Release",
        juce::NormalisableRange<float> { 0.0f, 3.0f, 0.001f, 0.3f }, 0.2f));

    // Filter
    params.push_back(std::make_unique<juce::AudioParameterChoice>("FILTERTYPE", "Filter Type",
        juce::StringArray{ "Low-Pass", "Band-Pass", "High-Pass" }, 0));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("FILTERCUTOFF", "Filter Cutoff",
        juce::NormalisableRange<float> { 20.0f, 20000.0f, 0.1f, 0.6f }, 20000.0f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("FILTERRES", "Filter Resonance",
        juce::NormalisableRange<float> { 1.0f, 10.0f, 0.1f}, 1.0f));

    // Reverb
    params.push_back(std::make_unique<juce::AudioParameterFloat>("REVERBROOM", "Room Size",
        juce::NormalisableRange<float> { 0.0f, 1.0f, 0.001f}, 0.0f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("REVERBDAMP", "Damping",
        juce::NormalisableRange<float> { 0.0f, 1.0f, 0.001f}, 0.0f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("REVERBWET", "Wet",
        juce::NormalisableRange<float> { 0.0f, 1.0f, 0.001f}, 0.0f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("REVERBDRY", "Dry",
        juce::NormalisableRange<float> { 0.0f, 1.0f, 0.001f}, 0.0f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("REVERBWIDTH", "Width",
        juce::NormalisableRange<float> { 0.0f, 1.0f, 0.001f}, 0.0f));
    //params.push_back(std::make_unique<juce::AudioParameterBool>("REVERBFREEZE", "Freeze", false));

    // Chorus
    params.push_back(std::make_unique<juce::AudioParameterFloat>("CHORUSRATE", "Rate",
        juce::NormalisableRange<float> { 0.0f, 99.999f, 0.001f}, 0.0f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("CHORUSDEPTH", "Depth",
        juce::NormalisableRange<float> { 0.0f, 1.0f, 0.001f}, 0.0f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("CHORUSDELAY", "Delay",
        juce::NormalisableRange<float> { 1.001f, 99.999f, 0.001f, 0.6f}, 1.1f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("CHORUSFEEDBACK", "Feedback",
        juce::NormalisableRange<float> { -1.0f, 1.0f, 0.001f}, 0.0f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("CHORUSMIX", "Mix",
        juce::NormalisableRange<float> { 0.0f, 1.0f, 0.001f}, 0.0f));

    //Gain
    params.push_back(std::make_unique<juce::AudioParameterFloat>("GAIN", "Gain",
        juce::NormalisableRange<float> {-100.0f , 12.0f, 0.1f}, -12.0f));

    return { params.begin(), params.end() };
}