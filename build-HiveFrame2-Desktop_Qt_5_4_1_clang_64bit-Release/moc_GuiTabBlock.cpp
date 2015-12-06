/****************************************************************************
** Meta object code from reading C++ file 'GuiTabBlock.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../HiveFrame2-opt-GUI/GuiTabBlock.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'GuiTabBlock.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_GuiTabBlock_t {
    QByteArrayData data[5];
    char stringdata0[60];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_GuiTabBlock_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_GuiTabBlock_t qt_meta_stringdata_GuiTabBlock = {
    {
QT_MOC_LITERAL(0, 0, 11), // "GuiTabBlock"
QT_MOC_LITERAL(1, 12, 13), // "changeBtnLine"
QT_MOC_LITERAL(2, 26, 0), // ""
QT_MOC_LITERAL(3, 27, 15), // "changeWindowBtn"
QT_MOC_LITERAL(4, 43, 16) // "recoverWindowBtn"

    },
    "GuiTabBlock\0changeBtnLine\0\0changeWindowBtn\0"
    "recoverWindowBtn"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_GuiTabBlock[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   29,    2, 0x08 /* Private */,
       3,    0,   30,    2, 0x08 /* Private */,
       4,    0,   31,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void GuiTabBlock::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        GuiTabBlock *_t = static_cast<GuiTabBlock *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->changeBtnLine(); break;
        case 1: _t->changeWindowBtn(); break;
        case 2: _t->recoverWindowBtn(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject GuiTabBlock::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_GuiTabBlock.data,
      qt_meta_data_GuiTabBlock,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *GuiTabBlock::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *GuiTabBlock::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_GuiTabBlock.stringdata0))
        return static_cast<void*>(const_cast< GuiTabBlock*>(this));
    return QWidget::qt_metacast(_clname);
}

int GuiTabBlock::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 3)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 3;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
