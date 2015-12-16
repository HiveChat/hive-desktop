/****************************************************************************
** Meta object code from reading C++ file 'GuiChatStack.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../HiveFrame2-opt-GUI/GuiChatStack.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'GuiChatStack.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_GuiChatStack_top_bar_t {
    QByteArrayData data[1];
    char stringdata0[21];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_GuiChatStack_top_bar_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_GuiChatStack_top_bar_t qt_meta_stringdata_GuiChatStack_top_bar = {
    {
QT_MOC_LITERAL(0, 0, 20) // "GuiChatStack_top_bar"

    },
    "GuiChatStack_top_bar"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_GuiChatStack_top_bar[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

       0        // eod
};

void GuiChatStack_top_bar::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

const QMetaObject GuiChatStack_top_bar::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_GuiChatStack_top_bar.data,
      qt_meta_data_GuiChatStack_top_bar,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *GuiChatStack_top_bar::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *GuiChatStack_top_bar::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_GuiChatStack_top_bar.stringdata0))
        return static_cast<void*>(const_cast< GuiChatStack_top_bar*>(this));
    return QWidget::qt_metacast(_clname);
}

int GuiChatStack_top_bar::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
struct qt_meta_stringdata_GuiChatStack_chat_widget_t {
    QByteArrayData data[4];
    char stringdata0[48];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_GuiChatStack_chat_widget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_GuiChatStack_chat_widget_t qt_meta_stringdata_GuiChatStack_chat_widget = {
    {
QT_MOC_LITERAL(0, 0, 24), // "GuiChatStack_chat_widget"
QT_MOC_LITERAL(1, 25, 13), // "addChatBubble"
QT_MOC_LITERAL(2, 39, 0), // ""
QT_MOC_LITERAL(3, 40, 7) // "message"

    },
    "GuiChatStack_chat_widget\0addChatBubble\0"
    "\0message"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_GuiChatStack_chat_widget[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   19,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void, QMetaType::QString,    3,

       0        // eod
};

void GuiChatStack_chat_widget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        GuiChatStack_chat_widget *_t = static_cast<GuiChatStack_chat_widget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->addChatBubble((*reinterpret_cast< QString(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject GuiChatStack_chat_widget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_GuiChatStack_chat_widget.data,
      qt_meta_data_GuiChatStack_chat_widget,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *GuiChatStack_chat_widget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *GuiChatStack_chat_widget::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_GuiChatStack_chat_widget.stringdata0))
        return static_cast<void*>(const_cast< GuiChatStack_chat_widget*>(this));
    return QWidget::qt_metacast(_clname);
}

int GuiChatStack_chat_widget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 1)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 1;
    }
    return _id;
}
struct qt_meta_stringdata_GuiChatStack_message_editor_t {
    QByteArrayData data[1];
    char stringdata0[28];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_GuiChatStack_message_editor_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_GuiChatStack_message_editor_t qt_meta_stringdata_GuiChatStack_message_editor = {
    {
QT_MOC_LITERAL(0, 0, 27) // "GuiChatStack_message_editor"

    },
    "GuiChatStack_message_editor"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_GuiChatStack_message_editor[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

       0        // eod
};

void GuiChatStack_message_editor::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

const QMetaObject GuiChatStack_message_editor::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_GuiChatStack_message_editor.data,
      qt_meta_data_GuiChatStack_message_editor,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *GuiChatStack_message_editor::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *GuiChatStack_message_editor::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_GuiChatStack_message_editor.stringdata0))
        return static_cast<void*>(const_cast< GuiChatStack_message_editor*>(this));
    return QWidget::qt_metacast(_clname);
}

int GuiChatStack_message_editor::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
struct qt_meta_stringdata_GuiChatStack_t {
    QByteArrayData data[1];
    char stringdata0[13];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_GuiChatStack_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_GuiChatStack_t qt_meta_stringdata_GuiChatStack = {
    {
QT_MOC_LITERAL(0, 0, 12) // "GuiChatStack"

    },
    "GuiChatStack"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_GuiChatStack[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

       0        // eod
};

void GuiChatStack::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

const QMetaObject GuiChatStack::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_GuiChatStack.data,
      qt_meta_data_GuiChatStack,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *GuiChatStack::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *GuiChatStack::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_GuiChatStack.stringdata0))
        return static_cast<void*>(const_cast< GuiChatStack*>(this));
    return QWidget::qt_metacast(_clname);
}

int GuiChatStack::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
QT_END_MOC_NAMESPACE
