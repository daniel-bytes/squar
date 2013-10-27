#include "stdafx.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

#include "../Source/Oscillator.h"
#include "../Source/Parameters.h"
#include "../JuceLibraryCode/JuceHeader.h"

namespace squarunittests
{
	TEST_CLASS(ParameterTests)
	{
	public:
		
		TEST_METHOD(Parameters_TestOscillatorParameters)
		{
			//Oscillator osc1(1);
			//Oscillator osc2(2);

			//Parameters parameters;
			//parameters.registerListener(&osc1);
			//parameters.registerListener(&osc2);

			//Assert::AreEqual(juce::String("").toRawUTF8(), parameters.get(0)->name.toRawUTF8());
		}

	};
}