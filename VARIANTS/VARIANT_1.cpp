#include <iostream>
#include <Windows.h>
#include <string>

enum class ThId {
	TH_A,
	TH_B,
	TH_C,
	TH_D,
	TH_E,
	TH_F,
	TH_G,
	TH_H,
	TH_I,
	//TH_K,
	TH_M,
	NONE
};

//enum class ThSt {
//	IS_STARTED,
//	IS_FINISHED,
//};

DWORD WINAPI threadProcess(ThId threadId);
void init();
void go();
bool openFrom(unsigned short int);
void enqueueVertex(unsigned short int vertex);		// Поставить вершину в очередь рассмотрения
void dequeueVertex(unsigned short int vertex);		// Удалить вершину из очереди рассмотрения
bool isEnqueuedVertex(unsigned short int vertex);	// Проверить, находится ли вершина в очереди
void enqueueThread(ThId thId);						// Поставить поток в очередь на запуск
//void dequeueThread(ThId thId);					// Удалить поток из очереди на запуск
bool isFinishedThread(ThId thId);					// Проверить, завершил ли поток работу
bool isEnqueuedThread(ThId thId);					// Проверить, находится ли поток в очереди на запуск
bool isDoneVertex(unsigned short int vertex);		// Проверить, что все входящие в вершину потоки завершили работу
void printThreadId(ThId thId);

const unsigned short int THREADS_NUMBER = 10;
const unsigned short int MAX_SEM_NUMBER = 4;
const unsigned short int VERTICES_NUMBER = 7;
HANDLE mutex;
HANDLE semaphore;
bool threadsToRun[THREADS_NUMBER];		// Флаги потоков, подлежащих запуску
//bool threadsToClose[THREADS_NUMBER];	// Флаги потоков, завершивших работу
bool currentVertices[VERTICES_NUMBER];	// Флаги вершин, подлежащих рассмотрению
HANDLE arrThreads[THREADS_NUMBER];		// Массив потоков


char threadsNames[THREADS_NUMBER] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I'/*, 'K'*/, 'M'};
ThId threadsMap[7][7] = {
//			0			1			2			3			 4			   5			6
	{ThId::NONE, ThId::TH_A, ThId::TH_C, ThId::TH_D, ThId::TH_E, ThId::NONE, ThId::NONE},	// 0
	{ThId::NONE, ThId::NONE, ThId::TH_B, ThId::NONE, ThId::NONE, ThId::NONE, ThId::NONE},	// 1
	{ThId::NONE, ThId::NONE, ThId::NONE, ThId::NONE, ThId::TH_G, ThId::TH_H, ThId::NONE},	// 2
	{ThId::NONE, ThId::NONE, ThId::NONE, ThId::NONE, ThId::TH_F, ThId::NONE, ThId::NONE},	// 3
	{ThId::NONE, ThId::NONE, ThId::NONE, ThId::NONE, ThId::NONE, ThId::TH_I, ThId::NONE},	// 4
	{ThId::NONE, ThId::NONE, ThId::NONE, ThId::NONE, ThId::NONE, ThId::NONE, ThId::TH_M},	// 5
	{ThId::NONE, ThId::NONE, ThId::NONE, ThId::NONE, ThId::NONE, ThId::NONE, ThId::NONE},	// 6
};



std::string variant1() {
	init();
	go();
	WaitForMultipleObjects(THREADS_NUMBER, arrThreads, TRUE, INFINITE);

	//system("Pause");

	return "";
}

void init() {
	int i;
	DWORD threadId;

	for (i = 0; i < THREADS_NUMBER; i++) {
		arrThreads[i] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE) threadProcess, (LPVOID) i/*static_cast<ThId>(i)*/, 0, &threadId);
	}

	for (i = 0; i < VERTICES_NUMBER; i++) {
		currentVertices[i] = false;
	}

	for (i = 0; i < THREADS_NUMBER; i++) {
		threadsToRun[i] = false;
	}

	/*for (i = 0; i < THREADS_NUMBER; i++) {
		threadsToClose[i] = false;
	}*/

	currentVertices[0] = true;

	semaphore = CreateSemaphore(NULL, MAX_SEM_NUMBER, MAX_SEM_NUMBER, NULL);
	mutex = CreateMutex(NULL, FALSE, NULL);
}

//void printThreadState(ThId thIds, ThSt thSt) {
//	switch (thSt) {
//	case ThSt::IS_STARTED:
//		printf("Thread %c is started\n", threadsNames[ static_cast<int>(thIds) ]);
//		break;
//	case ThSt::IS_FINISHED:
//		printf("Thread %c is finished\n", threadsNames[ static_cast<int>(thIds) ]);
//		break;
//	}
//}

//bool isToClose(ThId thIds) {
//	return threadsToRun[static_cast<int>(thIds)];
//}

void go() {
	//while (!closeFrom(VERTICES_NUMBER - 1)) {
	//	for (int i = 0; i < VERTICES_NUMBER; i++) {
	//		if (currentVertices[i]) {
	//			if (closeFrom(i)) {
	//				openFrom(i);
	//				//i = VERTICES_NUMBER;
	//			}
	//		}
	//	}
	//}

	while (/*WaitForMultipleObjects(THREADS_NUMBER, arrThreads, TRUE, INFINITE) != WAIT_OBJECT_0*/ !openFrom(VERTICES_NUMBER - 1)) {
		for (int i = 0; i < VERTICES_NUMBER; i++) {
			if (isEnqueuedVertex(i)) {
				openFrom(i);
			}
		}
	}
}

 //Закрывает потоки, возвращает TRUE, если потоки подлежали закрытию, и FALSE - в противном случае
//bool closeFrom(unsigned short int vertex) {
//	bool isToClose = true; // Флаг ЗАКРЫТЬ_ВСЕ_ПОТОКИ
//	DWORD exitCodeThread;
//
//	 Если НЕ ВСЕ(!) потоки, ведущие к вершине vertex, запущены, не закрывать их
//	for (int i = 0; i < VERTICES_NUMBER; i++) {
//		if (threadsMap[i][vertex] != ThId::NONE) {
//			if (arrThreads[ static_cast<int>(threadsMap[i][vertex]) ] == NULL) {
//				isToClose = false;
//			}
//		}
//	}
//
//	 Закрыть потоки, если необходимо
//	if (isToClose) {
//		for (int i = 0; i < VERTICES_NUMBER; i++) {
//			if (threadsMap[i][vertex] != ThId::NONE) {
//				threadsToRun[ static_cast<int>(threadsMap[i][vertex]) ] = true;
//				printThreadState(threadsMap[i][vertex], ThSt::IS_FINISHED);
//			}
//		}
//	}
//
//	return isToClose;
//}

// Открывает потоки из определённой вершины, изменяет список вершин currentVertices
bool openFrom(unsigned short int vertex) {
	DWORD threadId;
	bool flag = false;
	// Исключить vertex из очереди рассмотрения
	//currentVertices[vertex] = false;

	if (isDoneVertex(vertex)) {
		flag = true;
		dequeueVertex(vertex);
		// Запускаются исходящие из vertex потоки
		for (int i = 0; i < VERTICES_NUMBER; i++) {
			if (threadsMap[vertex][i] != ThId::NONE) {
				//arrThreads[ static_cast<int>(threadsMap[vertex][i]) ] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE) threadProcess, (LPVOID) threadsMap[vertex][i], 0, &threadId);
				enqueueVertex(i);
				enqueueThread(threadsMap[vertex][i]);
			}
		}
	}

	return flag;
}

DWORD WINAPI threadProcess(ThId threadId) {
	DWORD waitResult;
	int syncMode;

	//printThreadState(threadId, ThSt::IS_STARTED);

	syncMode = static_cast<int>(threadId) % (THREADS_NUMBER / 3);	// Классификация запускаемых потоков по способу их синхронизации
	switch (syncMode) {
	case 0:															// Нет синхронизации
		while (true) {
			if (isEnqueuedThread(threadId)) {
				printThreadId(threadId);
				//dequeueThread(threadId);
				return NULL;
			}
		}
		break;
	case 1:															// Синхронизация через семафор
		while (true) {
			if (isEnqueuedThread(threadId)) {
				waitResult = WaitForSingleObject(semaphore, 0);
				switch (waitResult) {
				case WAIT_OBJECT_0:
					printThreadId(threadId);
					//dequeueThread(threadId);
					if (!ReleaseSemaphore(semaphore, 1, NULL)) {
						printf("ReleaseSemaphore error: %d\n", GetLastError());
					}
					return NULL;
					//break;
				case WAIT_TIMEOUT:
					printf("Thread %d: wait timed out\n", GetCurrentThreadId());
					break;
				}
			}
		}
		break;
	case 2:															// Синхронизация через мьютекс
		while (true) {
			if (isEnqueuedThread(threadId)) {
				waitResult = WaitForSingleObject(mutex, INFINITE);
				switch (waitResult) {
				case WAIT_OBJECT_0:
					printThreadId(threadId);
					//dequeueThread(threadId);
					if (!ReleaseMutex(mutex)) {
						printf("ReleaseMutex error: %d\n", GetLastError());
					}
					return NULL;
					//break;
				case WAIT_TIMEOUT:
					printf("Thread %d: wait timed out\n", GetCurrentThreadId());
					break;
				}
			}
		}
		break;
	}
	return 0;
}

void enqueueVertex(unsigned short int vertex) {
	currentVertices[vertex] = true;
}

void dequeueVertex(unsigned short int vertex) {
	currentVertices[vertex] = false;
}

bool isEnqueuedVertex(unsigned short int vertex) {
	return currentVertices[vertex];
}

void enqueueThread(ThId threadId) {
	threadsToRun[static_cast<int>(threadId)] = true;
}

bool isFinishedThread(ThId threadId) {
	return (WaitForSingleObject(arrThreads[ static_cast<int>(threadId)], NULL) == WAIT_OBJECT_0);
}

bool isEnqueuedThread(ThId threadId) {
	return threadsToRun[static_cast<int>(threadId)];
}

bool isDoneVertex(unsigned short int vertex) {
	bool flag = true;

	// Если хотя бы один поток все ещё работает, присвоить флагу false
	for (int i = 0; i < VERTICES_NUMBER; i++) {
		if (threadsMap[i][vertex] != ThId::NONE) {
			if (!isFinishedThread(threadsMap[i][vertex])) {
				flag = false;
			}
		}
	}

	return flag;
}

void printThreadId(ThId threadId) {
	printf("%c\n", threadsNames[ static_cast<int>(threadId) ]);
}
