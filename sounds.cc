// Any sounds, including the soundtrack and various sound design, will be here. - GIANNI 
#include <iostream>
#include <string>
#include "ColorGrid.h"
#include "Bridges.h"
#include "Color.h"
#include "AudioClip.h"

using namespace std;
using namespace bridges;

int main(int argc **argv){
    // Initialize Bridges
    Bridges bridges (ASSIGNMENT_NUMBER, USER_ID, API_KEY);

    // set title and description
    bridges.setTitle("Audio Wave");
    bridges.setDescription("Create the wave form of an audio file");
    
        /*
        use different colors for the background of the color grid and the wave
        */ 
        ColorGrid cg = ColorGrid(1080, 1920, color);
        
        /*
        get the audio file by using its name
        */
        
        // get samples from the audio file
        
            
        /*
        average the samples.
        
        keep in mind that the audio's sampling rate
        is given in samples per second
        
        samples range from -1 to 1
        */
        
        /*
        plot the averages onto the color grid to 
        create the wave form of the audio
        
        keep in mind that the origin of the color grid
        is on the top left corner with y increasing 
        downwards
        */
        
        /*
        fill the wave form starting from the middle of the grid
        to the point that was plotted earlier
        */
       
       // visualization
        bridges.setDataStructure(cg);
        bridges.visualize();
}
