// Any sounds, including the soundtrack and various sound design, will be here. - GIANNI 
#include "AudioClip.h"
#include <iostream>
#include <fstream>
#include "Bridges.h"
#include <math.h>

using namespace std;
using namespace bridges;

AudioClip mixFadeClips(const AudioClip& ac1, const AudioClip& ac2, int fadeDuration, int duration) {
  if (ac1.getSampleRate() != ac2.getSampleRate()) {
    throw "can't mix audio clips of varying rates";
  }
  
  // sample count = sample rate * number of seconds
  int SAMPLE_RATE = ac1.getSampleRate();
    int sampleCount = SAMPLE_RATE * duration;
    
    AudioClip acMix = AudioClip(sampleCount, 1, ac1.getSampleBits(), SAMPLE_RATE);
    
    // Get half of the song for the fade center point
    int center = acMix.getSampleCount() / 2;

    //  Get the number of samples that the songs should fade in/out
    int fadeSamples = SAMPLE_RATE * fadeDuration;
    
    // Ensure the fade duration does not exceed the clip duration
    fadeSamples = min(fadeSamples, acMix.getSampleCount());
    
    // Get half of the fade samples for easier centering on the clip
    // ensure the samples are correctly split when of an odd number
    int fadeHalf1 = fadeSamples / 2;
    int fadeHalf2 = fadeHalf1 - (fadeSamples / 2);
    
    // Calculate the start, end, and length of the fade section
    int start = center - fadeHalf1;
    int end = center + fadeHalf2;
    
    // Loop through the samples of both clips and use the average amplitude value
    for (int i = 0; i < acMix.getSampleCount(); i++) {
        // Get the two samples to be mixed
        // sample1 starts at full amplitude and fades out after start until end
        // sample2 starts at 0 amplitude and fades in after start until end
        int sample1 = (int)(ac1.getSample(0, i) * (max(0, fadeSamples - (i - start)) / (float)fadeSamples));
        int sample2 = 0;

        if (i >= start)
            sample2 = (int)(ac2.getSample(0, i) * (min(fadeSamples, (i - start)) / (float)fadeSamples));
            
        acMix.setSample(0, i, (sample1 + sample2) / 2);
    }
    
    return acMix;
}

AudioClip mixFadeClips(AudioClip ac1, AudioClip ac2) {
    // If no duration is given then just use the minimum song duration
    int duration = min(ac1.getSampleCount() / ac1.getSampleRate(), ac2.getSampleCount()  / ac2.getSampleRate());

    // If no fade duration is given then use half the total duration
    int fadeDuration = duration / 2;
    
    return mixFadeClips(ac1, ac2, fadeDuration, duration);
}

int main() {
    Bridges bridges = Bridges(133, "BRIDGES_USER_ID", "BRIDGES_API_KEY");
    bridges.setTitle("Audio Mixing");
    bridges.setDescription("Fading two audio clips together");

    // Load the clips

    AudioClip mainMenu = AudioClip("menu.wav");
    bridges.setDataStructure(mainMenu);
    bridges.visualize();

    AudioClip theBeach = AudioClip("beach theme.wav") 
    bridges.setDataStructure(theBeach);
    bridges.visualize();
        
    // Apply fade mixing to the two AudioClips and visualize
    AudioClip acFadeMix = mixFadeClips(mainMenu, theBeach);
    bridges.setDataStructure(acFadeMix);
    bridges.visualize();

    return 0;
}
