#pragma once
#include "source.h"

DWORD WINAPI sqrt_(LPVOID lpParameter)
{
    HANDLE result = CreateMailslot(L"\\\\.\\mailslot\\sum", 0, MAILSLOT_WAIT_FOREVER, NULL);

    HANDLE third_semafor = OpenSemaphore(EVENT_ALL_ACCESS, TRUE, L"third_semafor");
    HANDLE fourth_semafor = OpenSemaphore(EVENT_ALL_ACCESS, TRUE, L"fourth_semafor");

    while (true) {
        WaitForSingleObject(third_semafor, INFINITE);

        std::cout << "\n" << "DEBUG OUT: THIRD PROGRAM" << std::endl;
        std::cout << "\n" << "DEBUG OUT: Program is calculating sqrt of sum of a and b now!" << std::endl;

        int_convert received_sum;
        double_convert mresult;

        DWORD real_reading_sum = 0;
        DWORD real_writing_res = 0;

        ReadFile(result, &received_sum.bytes, sizeof(int), &real_reading_sum, NULL);

        HANDLE res = CreateFile(L"\\\\.\\mailslot\\res", GENERIC_WRITE, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);

        mresult.value = sqrt(received_sum.value);

        WriteFile(res, mresult.bytes, sizeof(double), &real_writing_res, NULL);

        CloseHandle(result);

        std::cout << "\n" << "Function result - sqrt of (a*a + b*b): " << mresult.value << std::endl;
        std::cout << "\n" << "DEBUG OUT: THIRD PROGRAM is terminating now!" << std::endl;

        ReleaseSemaphore(fourth_semafor, 1, NULL);
    }
    return 0;
}