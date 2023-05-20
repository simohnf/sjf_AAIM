/// @file
///	@ingroup 	minexamples
///	@copyright	Copyright 2018 The Min-DevKit Authors. All rights reserved.
///	@license	Use of this source code is governed by the MIT License found in the License.md file.

#include "c74_min.h"
#include "../../../sjf_AAIMCplusplus/sjf_AAIM_rhythmGen.h"

using namespace c74::min;


class sjf_AAIM_rhythmGen_tilde : public object<sjf_AAIM_rhythmGen_tilde>, public sample_operator<1, 5> {
public:
    MIN_DESCRIPTION	{"Stochastically generated rhythmic variations on basic phase ramp."};
    MIN_TAGS		{"algorithmic music"};
    MIN_AUTHOR		{"sjf"};
    MIN_RELATED		{"phasor~, sjf.AAIM_patternVary~"};

    inlet<>     in1   { this, "(signal) phase ramp input" };
    outlet<>    out1  { this, "(signal) rhythm gen phase ramps", "signal" };
    outlet<>    out2  { this, "(signal) velocity: 0 --> 1", "signal" };
    outlet<>    out3  { this, "(signal) rests: 0 if rest", "signal" };
    outlet<>    out4  { this, "(signal) current division", "signal" };
    outlet<>    out5  { this, "(signal) number of beats for current division to synchronise", "signal" };
    outlet<>    dumpOut  { this, "(anything) dump: outputs a list of all current settings"};

    
    samples<5> operator()(sample input) {
        return m_rGen.runGenerator( input );
    }

    // post to max window == but only when the class is loaded the first time
    message<> maxclass_setup { this, "maxclass_setup",
        MIN_FUNCTION {
            cout << "AAIM_rhythmGen" << endl;
            return {};
        }
    };
    //============================================================
    //      THESE FUNCTIONS ALLOW INTERACTION WITH THE AAIM Rhythm Gen PARAMETERS
    message<> complexity  {this, "complexity", "This sets the probability of any of the various user set divisions being chosen rather than the basic just the underlying pulse.",
        MIN_FUNCTION {
            m_rGen.setComplexity( args[ 0 ] );
            return {};
        }
    };
    
    message<> rests  {this, "rests", "This sets the probability of rests being inserted into the pattern, these rests are output from the third inlet to allow different processing.",
        MIN_FUNCTION {
            m_rGen.setRests( args[ 0 ] );
            return {};
        }
    };
    
    message<> nBeats  {this, "nBeats", "This sets the number of beats in the rhythmic pattern, this defaults to 8.",
        MIN_FUNCTION {
            m_rGen.setNumBeats( args[ 0 ] );
            return {};
        }
    };
    
    message<> ioiProb  {this, "ioiProb", "Send a pair of values to set the probability for a specific rhythmic variation of the underlying pulse. ioiProb division probability (e.g. [ioiProb 0.5 1] would set the chance of half the normal rate to be triggered to 1; [ioiProb 1.5 0.2] would set the chance of a dotted note equal to 1.5 times the normal rate to be triggered to 0.2.",
        MIN_FUNCTION {
            if ( args.size() < 2 )
                return {};
            m_rGen.setIOIProbability( args[ 0 ], args[ 1 ] );
            return {};
        }
    };
    
    message<> clearProbs  {this, "clearProbs", "This will clear and reset the list of IOI probabilities",
        MIN_FUNCTION {
            m_rGen.clearIOIProbabilities();
            return {};
        }
    };
    
    message<> dump  {this, "dump", "This outputs a list of all of the current settings out the fourth outlet.",
        MIN_FUNCTION {
            auto outString = std::string{};
            outString = "nBeats " + std::to_string( m_rGen.getNumBeats() );
            dumpOut.send( outString );

            outString = "complexity " + std::to_string( m_rGen.getComplexity() );
            dumpOut.send( outString );

            outString = "rests " + std::to_string( m_rGen.getRests() );
            dumpOut.send( outString );
            
            auto ioiProbs = m_rGen.getIOIProbabilities( );
            for ( size_t i = 0; i < ioiProbs.size(); i++ )
            {
                outString = "ioiProbs ";
                for ( size_t j = 0; j < ioiLabels.size(); j++ )
                        outString += ioiLabels[ j ] + " " + std::to_string(ioiProbs[ i ][ j ]) + " ";
                dumpOut.send( outString );
            }
            
            outString = "baseIndispensibility ";
            auto bInd = m_rGen.getBaseindispensability();
            for ( size_t i = 0; i <  bInd.size(); i++ )
            {
                outString += std::to_string(bInd[ i ]) + " ";
            }
            dumpOut.send( outString );
            
            return {};
        }
    };
    
    //============================================================
private:
    void printIOIs()
    {
        auto ioiProbs = m_rGen.getIOIProbabilities( );
        for ( size_t i = 0; i < ioiProbs.size(); i++ )
        {
            cout << "ioiProbs: ";
            for ( size_t j = 0; j < ioiLabels.size(); j++ )
                cout << ioiLabels[ j ] << " " << ioiProbs[ i ][ j ] << "; ";
            cout << endl;
        }

    }
    
    void printBeatsAndIndis()
    {
        cout << "nBeats " << m_rGen.getNumBeats( ) << endl;
        cout << "baseIndis ";
        auto bInd = m_rGen.getBaseindispensability();
        for ( size_t i = 0; i <  bInd.size(); i++ )
        {
            cout << bInd[ i ] << " ";
        }
        cout << endl;
    }
    
    
    
    AAIM_rhythmGen< sample > m_rGen;
    std::array< std::string, 4 > ioiLabels{ "division", "probability", "repetitions", "baseIOIs" };
};


MIN_EXTERNAL(sjf_AAIM_rhythmGen_tilde);
