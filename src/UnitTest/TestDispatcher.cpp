#include "CppUnitTest.h"
#include "Message\MessageDispatcher.h"
#include "Message\MessageTag.h"

// Assert::AreEqual(), ...
// Logger::WriteMessage()
using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace xihad::ngn;

namespace xihad { namespace UnitTest 
{
	// TODO: �����޸�����
	TEST_CLASS(TestDispatcher)
	{
	public:
		// This method will run before every TestMethod in current class.
		TEST_METHOD_INITIALIZE(initState)
		{
		}

		// TODO: �޸Ĳ��Է�����������鿴���
		TEST_METHOD(TestTemplateFunction)
		{
			MessageDispatcher* dispatcher;
			MessageListener* listener;
			SourceFilter* filter;

			dispatcher->addListener("battle.fire", listener, filter);
		}

		// This method will run after run every TestMethod in current class.
		TEST_METHOD_CLEANUP(cleanupState)
		{
		}
	};
}}

