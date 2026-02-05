#ifndef SHIP_H
#define SHIP_H
#include <iostream>
#include "globals.h"
#include "log_folder.h"
#include <fstream>
#include <sstream>
class Ship
{
    public:
        
        /**
        * @brief Конструктор по умолчанию
        * @note Для задания используется setShip
        */
        Ship();

        /**
        * @brief Геттер для переменной _x
        */
        long int getX();

        /**
        * @brief Геттер для переменной _y
        */
        long int getY();


        // string getName();
        
        /**
        * @brief Геттер типа движения лодки 
        * @return {"DEFAULT", "GREEDY", "LAZY", "CRAZY"}
        */
        SHIP_MOVE_TYPE getType();

        /**
        * @brief Геттер количества пойманной рыбы за тик
        */
        uint8_t getIncrease();

        /**
        * @brief Геттер состояния лодки
        * @return {"DEFAULT","MOVE", "FISHING", "END", "DELETED"}
        */
        SHIP_ST getShipState();


        /**
        * @brief Геттер пойманной рыбы
        * @note Количество пойманной рыбы необходимо для удаления лодки
        */
        unsigned int getFishCount();


        void setShip(size_t x, size_t y);

        /**
        * @brief Присваивание лодке сотояния
        * @param state Состояние {"DEFAULT","MOVE", "FISHING", "END", "DELETED"}
        */
        void setShipState(SHIP_ST state);

        /**
        * @brief Запоминаем тик когда начали рыбалку
        * @param tick Значение тика
        * @note Рыбалка длится 1-3 такта. Необходима информация когда вылавливать рыбу
        */
        void setLockTick(ui tick);

        /**
        * @brief Установление типа движения лодки
        * @param type {DEFAULT GREEDY, LAZY, CRAZY, END}
        */
        void setMovementType(SHIP_MOVE_TYPE type);

        /**
        * @brief Вылавливание рыбы
        * @param tick Значение тика
        * @note В зависимости от тика рипнимается решение о вылове рыбы (прошло ли 1-3 тика)
        */
        bool catch_a_fish(ui tick);

        /**
        * @brief Увеличение рыбы 
        * @param dfish Количество выловленной рыбы
        */
        void increaseFish(uint8_t dfish);

        /**
        * @brief Движение лодки 
        * @param dx Перемещение по х
        * @param dy Перемещение по у
        */
        void moveTo(int8_t dx, int8_t dy);


        /**
        * @brief Логика движения лодки в зависимости от типа и состояния 
        */
        void rand_move();

        /**
        * @brief Проверка на выход лодки за границы точек с рыбой
        * @note Используется для удаления лодки 
        */
        bool valid_coord();
        
        /**
        * @brief Устанавливает признак завершения рыбалки
        * @note Используется для удаления лодки 
        */
        void setEndFlag(bool flag);
        

        virtual ~Ship();
        
        /**
        * @brief Переопределение оператора вывода для лодки. Выводится #
        */
        // friend ostream &operator << (ostream &os, Ship &sh);
       
        protected:
        
        private:
        /** 
        * @brief Координата х
        */
        long int _x;
        
        /** 
        * @brief Координата у
        */
        long int _y;
        
        /** 
        * @brief Тип движения лодки. По умолчанию (в начале до инициализации) DEFAULT 
        */
        SHIP_MOVE_TYPE _type = SHIP_MOVE_TYPE::DEFAULT;
        
        /** 
        * @brief Состояние лодки. По умолчанию (в начале до инициализации) DEFAULT 
        */
        SHIP_ST _state = SHIP_ST::DEFAULT;
        
        
        /** 
        * @brief Количество выловленной рыбы
        */
        ui _fish_count = 0;
        
        /** 
        * @brief Тик начала рыбалки (заброса сетей)
        */
        ui _local_tick = 0;
        
        /** 
        * @brief Количество выловленной рыбы на такте
        */
        ui _increase = 0;

        /** 
        * @brief Признак завершения рыбалки и отправления за контур
        */
        bool _end_flag = false;
    };
#endif // SHIP_H