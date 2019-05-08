/*----------------------------------/
/------------ThreadPool-------------/
/-------Hale Game Engine 2019-------/
/----Copyright © (See reference)----/
/----------------------------------*/
/*
  Reference: 	This is a slightly modified version of Sascha Willems C++ 11 thread pools.
  URL:			https://github.com/SaschaWillems/Vulkan/blob/master/base/threadpool.hpp
*/

#ifndef HALE3D_THREADPOOL
#define HALE3D_THREADPOOL

/* Standard include(s). */
#include <vector>
#include <thread>
#include <queue>
#include <mutex>
#include <condition_variable>

namespace Hale3D {
	class Thread {
	public:
		Thread();
		~Thread();
	
		void Push(const std::function<void()>& pFunction);
		void Wait();
		
	private:
		void _StartLoop();
		
		bool _destroying = false;
		std::thread _worker;
		std::queue<std::function<void()>> _jobQueue;
		std::mutex _queueMutex;
		std::condition_variable _condition;
	};
	
	struct ThreadPool {
		void SetThreadCount(uint32_t pCount);
		uint32_t GetThreadCount() const;
		void Wait();

		/* Template method(s). */
		/*
			ASyncForEach
			- Loops over each element in pIteratable and runs pJobPushFunc for each index passing a valid thread-pointer and "element index" (size_t) as arguments.
			- pRemainderFunc will be ran for each remaining object on the main thread, "element index" (size_t) is passed as an argument.
		*/
		template<typename _VECTOR> // TODO enable_if vector.
		void ASyncForEach(const _VECTOR& pIteratable, const std::function<void(Thread*, size_t)>& pJobPushFunc, const std::function<void(size_t)> pRemainderFunc) { // Thread* being a pointer to the thread we're pushing a job to. size_t being the "objIndex" in pIteratable[].
			if (pIteratable.size() <= GetThreadCount()) {
				// We have either more threads than objects, or the same # of both... therefore we can use one per object.
				for (size_t i = 0; i < pIteratable.size(); ++i) {
					pJobPushFunc(m_Threads[i].get(), i);
				}
			}
			else {
				// Use as many threads as possible to animate joints.
				uint32_t objectsPerThread = static_cast<uint32_t>(pIteratable.size() / GetThreadCount());
				size_t objIndex = 0;
				for (uint32_t i = 0; i < GetThreadCount(); ++i) {
					for (uint32_t k = 0; k < objectsPerThread; ++k) {
						pJobPushFunc(m_Threads[i].get(), objIndex++);
					}
				}

				// Handle the remainder (if any).
				uint32_t remainder = static_cast<uint32_t>(pIteratable.size() % GetThreadCount());
				for (uint32_t i = 0; i < remainder; ++i) { // Handle last entity(s) based on division remainder.
					pRemainderFunc(objIndex++);
				}
			}

			Wait();
		}
		
		std::vector<std::unique_ptr<Thread>> m_Threads;
	};
}

#endif