//
// Created by Kostya Bogatyrev on 13.04.2023.
//

#ifndef UNTITLED11_QTEXTSTREAM_H
#define UNTITLED11_QTEXTSTREAM_H


#include "QString.h"

class QTextStream {

public:
    QString readLine();

    bool atEnd();
};


#endif //UNTITLED11_QTEXTSTREAM_H
