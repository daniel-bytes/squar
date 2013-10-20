#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

#include "../Source/Utilities.h"

namespace shiftrunittests
{		
	TEST_CLASS(UtilitiesTests)
	{
	public:
		
		TEST_METHOD(TestClipFunction)
		{
			float value;

			value = clip(.5, 0, 1);
			Assert::AreEqual(.5f, value, 0.f);
			
			value = clip(.5f, 1, 2);
			Assert::AreEqual(1.f, value, 0.f);
			
			value = clip(.5f, 0, .4);
			Assert::AreEqual(.4f, value, 0.f);
		}
		
		TEST_METHOD(TestScaleFunction)
		{
			float value;

			value = scale(.25, 0, 100);
			Assert::AreEqual(25.f, value, 0.f);

			value = scale(.25, 20, 100);
			Assert::AreEqual(40.f, value, 0.f);

			value = scale(.25, -20, -100);
			Assert::AreEqual(-40.f, value, 0.f);

			value = scale(.25, 100, 20);
			Assert::AreEqual(80.f, value, 0.f);
		}
	};
}