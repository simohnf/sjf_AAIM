/// @file
///	@ingroup 	minexamples
///	@copyright	Copyright 2018 The Min-DevKit Authors. All rights reserved.
///	@license	Use of this source code is governed by the MIT License found in the License.md file.

#include "c74_min.h"
#include "../../../sjf_AAIMCplusplus/sjf_AAIM_patternVary.h"

using namespace c74::min;


class sjf_AAIM_patternVary_tilde : public object<sjf_AAIM_patternVary_tilde>, public sample_operator<2, 1> {
public:
    MIN_DESCRIPTION	{ "Generate variations on a given pattern." };
    MIN_TAGS		{ "algorithmic music" };
    MIN_AUTHOR		{ "sjf" };
    MIN_RELATED		{ "sjf.AAIM_rhythmGen~" };

    inlet<>     in1   { this, "(signal) phase ramp input of full pattern" };
    inlet<>    in2  { this, "(signal) triggerRamp, ramps for AAIM_rhythmGenTriggers", "signal" };
    outlet<>    out1  { this, "(signal) triggers", "signal" };
    outlet<>    dumpOut  { this, "(anything) dump: outputs a list of all current settings" };

    
    samples<2> operator()( sample currentBeat, sample triggerRamp ) {
        auto trig = 0.0f;
        if ( triggerRamp < (m_lastTriggerInput * 0.5) )
            if ( m_pVary.triggerBeat( currentBeat ) )
                trig = 1.0f;
//        auto output = ( triggerRamp < (m_lastTriggerInput * 0.5) ) && m_pVary.triggerBeat( currentBeat ) ? 1.0f : 0.0f;
        m_lastTriggerInput = triggerRamp;
        return { trig };
        
    }

    // post to max window == but only when the class is loaded the first time
    message<> maxclass_setup { this, "maxclass_setup",
        MIN_FUNCTION {
            cout << "AAIM_patternVary" << endl;
//            printIOIs();
//            printBeatsAndIndis();
            return {};
        }
    };
    //============================================================
    //      THESE FUNCTIONS ALLOW INTERACTION WITH THE AAIM Rhythm Gen PARAMETERS
    message<> fills  {this, "fills", "This sets the probability of additional fills being inserted into the pattern.",
        MIN_FUNCTION {
            m_pVary.setFills( args[ 0 ] );
            cout << "Fills " << m_pVary.getFills( ) << endl;
            return {};
        }
    };
    
//    message<> rests  {this, "rests", "This sets the probability of rests being inserted into the pattern, these rests are output from the third inlet to allow different processing.",
//        MIN_FUNCTION {
//            m_rGen.setRests( args[ 0 ] );
//            cout << "Rests " << m_rGen.getRests( ) << endl;
//            return {};
//        }
//    };
//
    message<> nBeats  {this, "nBeats", "This sets the number of beats in the pattern, this defaults to 8.",
        MIN_FUNCTION {
            m_pVary.setNumBeats( args[ 0 ] );
            cout << "nBeats " << m_pVary.getNumBeats() << endl;
//            printBeatsAndIndis();
            return {};
        }
    };
    
    message<> setBeat  {this, "setBeat", "This sets the state one of the beats in the pattern. e.g. [setBeat 0 1] sets the first beat on, [setBeat 3 0] sets the fouth beat off, etc.",
        MIN_FUNCTION {
            cout << "beat " << args[ 0 ] << " " << args[ 1 ] << endl;
            auto beatOn = ((float)args[ 1 ] > 0.5f) ? true : false;
            m_pVary.setBeat( args[ 0 ], beatOn );
//            printIOIs();
            return {};
        }
    };
    
//    message<> dump  {this, "dump", "This outputs a list of all of the current settings out the fourth outlet.",
//        MIN_FUNCTION {
//            auto outString = std::string{};
////            auto nBeats = m_rGen.getNumBeats;
//            outString = "nBeats " + std::to_string( m_rGen.getNumBeats() );
//            dumpOut.send( outString );
//
//            outString = "Complexity " + std::to_string( m_rGen.getComplexity() );
//            dumpOut.send( outString );
//
//            outString = "Rests " + std::to_string( m_rGen.getRests() );
//            dumpOut.send( outString );
//
//            auto ioiProbs = m_rGen.getIOIProbabilities( );
//            for ( size_t i = 0; i < ioiProbs.size(); i++ )
//            {
//                outString = "ioiProbs ";
//                for ( size_t j = 0; j < ioiLabels.size(); j++ )
//                        outString += ioiLabels[ j ] + " " + std::to_string(ioiProbs[ i ][ j ]) + " ";
//                dumpOut.send( outString );
//            }
//
//            outString = "baseIndispensibility ";
//            auto bInd = m_rGen.getBaseIndispensibility();
//            for ( size_t i = 0; i <  bInd.size(); i++ )
//            {
//                outString += std::to_string(bInd[ i ]) + " ";
//            }
//            dumpOut.send( outString );
//            return {};
//        }
//    };
    
    //============================================================
private:
//    void printIOIs()
//    {
//        auto ioiProbs = m_rGen.getIOIProbabilities( );
//        for ( size_t i = 0; i < ioiProbs.size(); i++ )
//        {
//            cout << "ioiProbs: ";
//            for ( size_t j = 0; j < ioiLabels.size(); j++ )
//                cout << ioiLabels[ j ] << " " << ioiProbs[ i ][ j ] << "; ";
//            cout << endl;
//        }
//
//    }
//
//    void printBeatsAndIndis()
//    {
//        cout << "nBeats " << m_rGen.getNumBeats( ) << endl;
//        cout << "baseIndis ";
//        auto bInd = m_rGen.getBaseIndispensibility();
//        for ( size_t i = 0; i <  bInd.size(); i++ )
//        {
//            cout << bInd[ i ] << " ";
//        }
//        cout << endl;
//    }
//
//
    
    AAIM_patternVary m_pVary;
    float m_lastTriggerInput = 1;
};


MIN_EXTERNAL(sjf_AAIM_patternVary_tilde);
