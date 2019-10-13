//Based on the layout of the Korg MS20 Synth

class SynthesizerInterface
{
private:
	//Master
	char MasterVolume;
	char Portamento;
	char MasterTune;
	char ModWheel;

	//Voltage Controlled Oscillator 1
	char VCO1Waveform;
	char VCO1Pulsewidth;
	char VCO1Scale;

	//Voltage Controlled Oscillator 2
	char VCO2Waveform;
	char VCO2Pitch;
	char VCO2Scale;
	
	//VCO Mixer
	char VCO1Level;
	char VCO2Level;
	
	//Voltage Controlled Highpass Filter
	char VCHFCutoffFreq;
	char VCHFPeak;

	//Voltage Controlled Lowpass Filter
	char VCLFCutoffFreq;
	char VCLFPeak;

	//Frequency Modulation
	char FMMGTEXT;
	char FMEG1EXT;

	//Cutoff Frequency Modulation 1
	char MGTEXT_1;
	char EG2EXT_1;

	//Cutoff Frequency Modulation 2
	char MGTEXT_2;
	char EG2EXT_2;

	//Modulation Generator
	char ModGenWaveform;
	char ModGenFreq;

	//Envelope Generator 1
	char EGDelayTime_1;
	char EGAttackTime_1;
	char EGReleaseTime_1;

	//Envelope Generator 2
	char EGHoldTime_2;
	char EGAttackTime_2;
	char EGDecayTime_2;
	char EGSustain_2;
	char EGReleaseTime_2;

	//External Signal Processor
	char ESPSignalLevel;
	char ESPLowCutFreq;
	char ESPHiCutFreq;
	char ESPCVAdjust;
	char ESPThreshLvl;

public:
	//Master
	void setMasterVolume(char vol);
	void setPortamento(char portamento);
	void setMasterTune(char mastertune);
	void setModWheel(char modwheel);

	//Voltage Controlled Oscillator 1
	void setVCO1Waveform(char waveform);
	void setVCO1Pulsewidth(char pulsewidth);
	void setVCO1Scale(char scale);

	//Voltage Controlled Oscillator 2
	void setVCO2Waveform(char waveform);
	void setVCO2Pitch(char pitch);
	void setVCO2Scale(char scale);

	//VCO Mixer
	void setVCO1Level(char level);
	void setVCO2Level(char level);

	//Voltage Controlled Highpass Filter
	void setVCHFCutoffFreq(char freq);
	void setVCHFPeak(char peak);

	//Voltage Controlled Lowpass Filter
	void setVCLFCutoffFreq(char freq);
	void setVCLFPeak(char peak);

	//Frequency Modulation
	void setFMMGTEXT(char val);
	void setFMEG1EXT(char val);

	//Cutoff Frequency Modulation 1
	void setMGTEXT_1(char val);
	void setEG2EXT_1(char val);

	//Cutoff Frequency Modulation 2
	void setMGTEXT_2(char val);
	void setEG2EXT_2(char val);

	//Modulation Generator
	void setModGenWaveform(char waveform);
	void setModGenFreq(char freq);

	//Envelope Generator 1
	void setEGDelayTime_1(char time);
	void setEGAttackTime_1(char time);
	void setEGReleaseTime_1(char time);

	//Envelope Generator 2
	void setEGHoldTime_2(char time);
	void setEGAttackTime_2(char time);
	void setEGDecayTime_2(char time);
	void setEGSustain_2(char time);
	void setEGReleaseTime_2(char time);

	//External Signal Processor
	void setESPSignalLevel(char level);
	void setESPLowCutFreq(char freq);
	void setESPHiCutFreq(char freq);
	void setESPCVAdjust(char adjust);
	void setESPThreshLvl(char level);
	

};

