#include "resources.h"
#include "main.h"
#include "init.h"
#include "log.h"
#include "request.h"
#include "response.h"

/*                  ---Определение функции main---
*   Функция main является точкой входа в программу и осуществляет вызов функций, необходимых для работы утилиты.
*   В качестве начальных входных параметров функция main получает набор аргументов argc и argv,
*       где argc - количество переданных параметров; 
*           argv - массив входных параметров, введенных пользователяем.
*   Пользователь может вводить любое кол-во параметров запуска, но корректно обрабатываться будет только последовательность 2 параметра.
*   Программа запускается в формате: ping <Ip-address OR HostName>
*                   ---Пример---
*               ping yandex.ru
*               где argc = 2;
*               Содержимое argv:
*               argv[0] = ping
*               argv[1] = yandex.ru
*               ---END ПРИМЕР---
*/
int main(int argc, char* argv[])
{
    // Тело программы

    setlocale(LC_ALL, "Russian");                   // Установка русского языка для правильности вывода русских символов
    returnCode = 0;
    listn = { 0 };
    Icmp = new char[1];
    pac = { 0 };
    Packet = { 0 };
    incr = 0;
    bf[BUFFER_SIZE] = { 0 };
    logger = {"", 0, 0};
    list_adr = { 0 };
    bnd = { 0 };
    out_ = { 0 };
    wsd = { 0 };
    Ip = new char[0];

    switch (createLog(logStream))                                                   // Создание лога и обработка его ошибок
    {
    case 0:                                                                         // Удачное выполнение функции
        break;
    case 1:                                                                         // Ошибка при выполнении
        returnCode = 10;
        return returnCode;                                                          
                                                                                    // Запись ошибки в лог
        break;
    }

    switch (checkArgs(argc, logger))                                                // Проверка входных аргументов (если есть ошибки - вывод куда-нибудь уже)
    {
    case 0:                                                                         // Удачное выполнение функции
        Ip = argv[1];                                                               // Пингуемый адрес.
        break;
    case 1:                                                                         // Ошибка при выполнении
        returnCode = 20;
                                                                                    // Запись ошибки в лог
        return returnCode;
    }

    switch(init(Ip, list_adr, bnd, out_, wsd, listn, logger))                       // Определение структур и сокета для работы
    {
    case 0:                                                                         // Успешное выполнение
        break;
    case 1:                                                                         // Ошибка при выполнении
        returnCode = 30;
                                                                                    // Запись ошибки в лог
        return returnCode;
    }

    switch (dnsCheck(list_adr, bnd, Ip, listn, logger))                          // Проверка на ввод DNS или обычного айпи
    {
    case 0:                                                                         // Успешное выполнение
        break;
    case 1:                                                                         // Ошибка при выполнении
        returnCode = 40;
                                                                                    // Запись ошибки в лог
        return returnCode;
    }

    switch (assembling(pac, Packet, Icmp))                                          // Сборка пакета + вычисление контрольной суммы
    {
    case 0:                                                                         // Успешное выполнение
        break;
    case 1:                                                                         // Ошибка при выполнении
        returnCode = 50;
                                                                                    // Запись ошибки в лог
        return returnCode;
    }

    while (incr < 6)                                                                // Цикл для отправки 6-ти эхо-запросов 
    {
        switch(request(Packet, listn, list_adr))                                    // Отправка пакета
        {
        case 0:                                                                     // Успешное выполнение
            break;
        case 1:                                                                     // Ошибка при выполнении
            returnCode = 60;
                                                                                    // Запись ошибки в лог
            return returnCode;
        }
        
        switch(response(listn, bf, out_, incr))                                     // Получение ответа
        {
        case 0:                                                                     // Успешное выполнение
            incr++;
            break;
        case 1:                                                                     // Ошибка при выполнении
            returnCode = 70;
                                                                                    // Запись ошибки в лог
            return returnCode;
            break;
        }
    }
    results();
    finish(Icmp, listn);
    return returnCode;
}