#pragma once

#include "Core.hpp"
#include "Core_Thread.hpp"
#include "Core_Vector.hpp"
#include "Core_TypeTraits.hpp"
#include "Core_Array.hpp"
#include "Core_TaskPool.hpp"
#include "Core_UniquePtr.hpp"
#include "Core_StronglyTypedId.hpp"

namespace Alba
{
	namespace Core
	{
		struct TaskThreadId_Tag {};
		typedef StronglyTypedId<uint32, TaskThreadId_Tag> TaskThreadId;

		inline constexpr TaskThreadId theMainThreadId(0);

		//-----------------------------------------------------------------------------------------
		// Name	:	TaskSystem
		// Desc	:	Multithreaded task system, executes a tree of tasks over several threads
		//-----------------------------------------------------------------------------------------
		class TaskSystem final
		{
			public:

				//=================================================================================
				// Public Static Methods
				//=================================================================================
				static void			Initialise(uint aThreadCount);
				static void			Shutdown();
				static TaskSystem&	GetMutable();

				static void			QueueTask(Task& aTask);

				//=================================================================================
				// Public Constructors
				//=================================================================================
				TaskSystem();
				~TaskSystem();
		
				//=================================================================================
				// Public Methods
				//================================================================================
				void				BeginFrame();
				void				EndFrame();

			private:

				//=================================================================================
				// Private Methods
				//=================================================================================
				void				InitialiseInternal(uint aThreadCount);
				void				ShutdownInternal();

				//=================================================================================
				// Private Data
				//=================================================================================
				Vector<thread>		myTaskThreads;
				Vector<TaskPool>	myTaskPools;
		};

		//-----------------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------------
		inline Task& CreateTask(TaskFunctionPtr aFunctionPtr)
		{
			return *TaskPool::CreateTask(aFunctionPtr);
		}

		//-----------------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------------
		template <typename TFunctionObject>
		inline Task& CreateTask(TFunctionObject&& anObject)
		{
			return *TaskPool::CreateTask(std::forward<TFunctionObject>(anObject));
		}

		//-----------------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------------
		template <typename TObjectType>
		inline Task& CreateTask(TObjectType* anInstance, TaskMemberFunctionPtr<TObjectType> aFunctionPtr)
		{
			return *TaskPool::CreateTask(anInstance, aFunctionPtr);
		}

		//-----------------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------------
		inline Task& CreateChildTask(Task& aParent, TaskFunctionPtr aFunctionPtr)
		{
			return *TaskPool::CreateTask(aParent, aFunctionPtr);
		}

		//-----------------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------------
		template <typename TFunctionObject>
		inline Task& CreateChildTask(Task& aParent, TFunctionObject&& anObject)
		{
			return *TaskPool::CreateTask(aParent, std::forward<TFunctionObject>(anObject));
		}

		//-----------------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------------
		template <typename TObjectType>
		inline Task& CreateChildTask(Task& aParent, TObjectType* anInstance, TaskMemberFunctionPtr<TObjectType> aFunctionPtr)
		{
			return *TaskPool::CreateTask(aParent, anInstance, aFunctionPtr);
		}

		//-----------------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------------
		inline void QueueTask(Task& aTask)
		{
			TaskSystem& taskSystem = TaskSystem::GetMutable();
			taskSystem.QueueTask(aTask);
		}
	}
}