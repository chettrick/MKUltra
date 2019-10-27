#include <iostream>

#include <cmath>

#include <portaudio.h>

#include "oscillator.h"
#include "envelope.h"
#include "instrument.h"

#ifndef M_PI
#define M_PI			(3.14159265)
#endif

#define SAMPLE_RATE		(44100)
#define TABLE_SIZE		(200)
#define FRAMES_PER_BUFFER	(paFramesPerBufferUnspecified)
#define STREAM_FLAGS		(paClipOff)

class Sound
{
public:
	Sound() : stream(0), phase(0)
	{
		/* Initialise sinusoidal wavetable. */
		for (int i = 0; i < TABLE_SIZE; i++) {
			sine[i] = (float)sin(((double)i / (double)TABLE_SIZE) * M_PI * 2.0);
		}
	}

	bool open(PaDeviceIndex index)
	{
		PaStreamParameters outputParameters;

		outputParameters.device = index;
		if (outputParameters.device == paNoDevice) {
			return false;
		}

		const PaDeviceInfo* pInfo = Pa_GetDeviceInfo(index);
		if (pInfo != 0) {
			printf("Output device name: '%s'\r", pInfo->name);
		}

		outputParameters.channelCount = 1; /* mono output */
		outputParameters.sampleFormat = paFloat32; /* 32 bit floating point output */
		outputParameters.suggestedLatency =
		    Pa_GetDeviceInfo(outputParameters.device)->defaultLowOutputLatency;
		outputParameters.hostApiSpecificStreamInfo = NULL;

		PaError err = Pa_OpenStream(
		    &stream,
		    NULL, /* no input */
		    &outputParameters,
		    SAMPLE_RATE,
		    FRAMES_PER_BUFFER,
		    STREAM_FLAGS,
		    &Sound::paCallback,
		    (void*)this /* To cast userData to type Sound*, */
		);

		if (err != paNoError) {
			return false;
		}

		return true;
	}

	bool close()
	{
		if (stream == 0) {
			return false;
		}

		PaError err = Pa_CloseStream(stream);
		stream = 0;

		return (err == paNoError);
	}

	bool start()
	{
		if (stream == 0) {
			return false;
		}

		PaError err = Pa_StartStream(stream);

		return (err == paNoError);
	}

	bool stop()
	{
		if (stream == 0) {
			return false;
		}

		PaError err = Pa_StopStream(stream);

		return (err == paNoError);
	}

private:
	int paCallbackMethod(const void *inputBuffer, void *outputBuffer,
	    unsigned long framesPerBuffer,
	    const PaStreamCallbackTimeInfo* timeInfo,
	    PaStreamCallbackFlags statusFlags)
	{
		float *out = (float*)outputBuffer;

		/* Prevent unused variable warnings. */
		(void)inputBuffer;
		(void)timeInfo;
		(void)statusFlags;

		for (unsigned long i = 0; i < framesPerBuffer; i++) {
			*out++ = sine[phase];
			phase += 1;
			if (phase >= TABLE_SIZE) {
				phase -= TABLE_SIZE;
			}
		}

		return paContinue;
	}

	/*
	 * This routine is called by the PortAudio engine when audio is needed.
	 */
	static int paCallback(const void *inputBuffer, void *outputBuffer,
	    unsigned long framesPerBuffer,
	    const PaStreamCallbackTimeInfo* timeInfo,
	    PaStreamCallbackFlags statusFlags,
	    void *userData)
	{
		/*
		 * Cast userData to type Sound*,
		 * to call the instance method paCallbackMethod.
		 */
		return ((Sound*)userData)->paCallbackMethod(inputBuffer, outputBuffer,
		    framesPerBuffer, timeInfo, statusFlags);
	}

	PaStream *stream;
	float sine[TABLE_SIZE];
	int phase;
};

class ScopedPaHandler
{
public:
	ScopedPaHandler() : _result(Pa_Initialize()) {}

	~ScopedPaHandler()
	{
		if (_result == paNoError) {
			Pa_Terminate();
		}
	}

	PaError result() const
	{
		return _result;
	}

private:
	PaError _result;
};
