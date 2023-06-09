/// @file
///	@ingroup 	minexamples
///	@copyright	Copyright 2018 The Min-DevKit Authors. All rights reserved.
///	@license	Use of this source code is governed by the MIT License found in the License.md file.

#include "c74_min.h"
#include "../../../sjf_AAIMCplusplus/sjf_AAIM_melodyVary.h"

using namespace c74::min;


class sjf_AAIM_melodyVary_tilde : public object<sjf_AAIM_melodyVary_tilde>, public sample_operator<3, 2> {
public:
    MIN_DESCRIPTION	{ "Stochastically generated variations on a given melody." };
    MIN_TAGS		{ "algorithmic music" };
    MIN_AUTHOR		{ "sjf" };
    MIN_RELATED		{ "sjf.AAIM_rhythmGen~, sjf.AAIM_patternVary~" };

    inlet<>     in1   { this, "(signal) phase ramp input of full pattern ( 0 --> nBeats )", "signal" };
    inlet<>    in2  { this, "(signal) ioi ramp, ramps from AAIM_rhythmGen", "signal" };
    inlet<>    in3  { this, "(signal) number of beats to synchronise, this is the number of beats for the current IOI chosen by the AAIM_rhythmGen to synchronise", "signal" };
    outlet<>    out1  { this, "(signal) notes", "signal" };
    outlet<>    out2  { this, "(signal) note lengths normalised to base ioi", "signal" };
    outlet<>    dumpOut  { this, "(anything) dump: outputs a list of all current settings" };

    
    samples<2> operator()( sample currentBeat, sample triggerRamp, sample beatsToSync  ) {
        // if nothing is connected to trigger ramp input just use the position in the current beat
        if ( !in2.has_signal_connection() )
            triggerRamp = currentBeat - (size_t)currentBeat;
        // if nothing is connected to beat sync input just use the position in the current beat
        if ( !in3.has_signal_connection() || !in2.has_signal_connection() )
            beatsToSync = 1.0;
        std::array< sample, 2 > outNote{ -1, -1 };
        if ( triggerRamp < (m_lastTriggerInput * 0.5) )
            outNote = m_mVary.triggerPitch( currentBeat, beatsToSync );
        m_lastTriggerInput = triggerRamp;
        return { outNote };
    }

    // post to max window == but only when the class is loaded the first time
    message<> maxclass_setup { this, "maxclass_setup",
        MIN_FUNCTION {
            cout << "AAIM_melodyVary" << endl;
            return {};
        }
    };
    //============================================================
    //      THESE FUNCTIONS ALLOW INTERACTION WITH THE AAIM Rhythm Gen PARAMETERS
    message<> melody  {this, "melody", "This sets the melody. It is expected as a list of pairs [ pitch, trigger type ]. Where the possible trigger types are rest(0), tie(1), newNote(2).",
        MIN_FUNCTION {
            cout << "melody input " << endl;
            auto length = args.size();
            if ( length < 2 )
                return {};
            else if ( length % 2 != 0 )
                length -= 1;
            auto melody = std::vector< std::array< size_t, 2 > >( length / 2 );
            melody.clear();
            for ( size_t i = 0; i < length; i+=2  )
                melody.emplace_back( std::array< size_t, 2 >{ args[ i ], args[ i+1 ] } );
            m_mVary.setMelody( melody );
            
            auto melOut = m_mVary.getMelody();
            for ( size_t i = 0; i < melOut.size(); i++ )
            {
                cout << "Note ";
                for ( size_t j = 0; j < melOut[ i ].size(); j++ )
                    cout << melOut[ i ][ j ] << " ";
                cout << endl;
            }
                
            auto pitches = m_mVary.getAvailablePitchClasses();
            cout << "Available Pitches ";
            for ( size_t i = 0; i < pitches.size(); i++ )
                cout << pitches[ i ] << " ";
            cout << endl;
            return {};
        }
    };
//
//    message<> nBeats  {this, "nBeats", "This sets the number of beats in the pattern, this defaults to 8.",
//        MIN_FUNCTION {
//            m_pVary.setNumBeats( args[ 0 ] );
//            return {};
//        }
//    };
//
//    message<> setBeat  {this, "setBeat", "This sets the state one of the beats in the pattern. e.g. [setBeat 0 1] sets the first beat on, [setBeat 3 0] sets the fouth beat off, etc.",
//        MIN_FUNCTION {
//            auto beatOn = ((float)args[ 1 ] > 0.0f) ? true : false;
//            m_pVary.setBeat( args[ 0 ], beatOn );
//            return {};
//        }
//    };
//
//    message<> dump  {this, "dump", "This outputs a list of all of the current settings out the fourth outlet.",
//        MIN_FUNCTION {
//            auto outString = std::string{};
//            outString = "nBeats " + std::to_string( m_pVary.getNumBeats() );
//            dumpOut.send( outString );
//
//            outString = "fills " + std::to_string( m_pVary.getFills() );
//            dumpOut.send( outString );
//
//            auto pattern = m_pVary.getPattern( );
//            for ( size_t i = 0; i < pattern.size(); i++ )
//            {
//                outString = "pattern ";
//                for ( size_t j = 0; j < pattern.size(); j++ )
//                {
//                    auto val = pattern[ i ] ? 1.0f : 0.0f;
//                    outString += std::to_string( val ) + " ";
//                }
//            }
//            dumpOut.send( outString );
//            return {};
//        }
//    };
//
    //============================================================
private:

    
    AAIM_melodyVary< sample > m_mVary;
    float m_lastTriggerInput = 1;
    
};


MIN_EXTERNAL(sjf_AAIM_melodyVary_tilde);
