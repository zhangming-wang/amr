/****************************************************************************
** Meta object code from reading C++ file 'nodeqthread.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../src/pc_software/src/nodeqthread/nodeqthread.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'nodeqthread.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_NodeQThread_t {
    QByteArrayData data[15];
    char stringdata0[332];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_NodeQThread_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_NodeQThread_t qt_meta_stringdata_NodeQThread = {
    {
QT_MOC_LITERAL(0, 0, 11), // "NodeQThread"
QT_MOC_LITERAL(1, 12, 22), // "motionStatusMsgChanged"
QT_MOC_LITERAL(2, 35, 0), // ""
QT_MOC_LITERAL(3, 36, 48), // "motion_status_msgs::msg::Moti..."
QT_MOC_LITERAL(4, 85, 16), // "serialMsgChanged"
QT_MOC_LITERAL(5, 102, 32), // "std_msgs::msg::String::SharedPtr"
QT_MOC_LITERAL(6, 135, 28), // "motionParamsServiceResponsed"
QT_MOC_LITERAL(7, 164, 68), // "motion_params_service::srv::M..."
QT_MOC_LITERAL(8, 233, 22), // "restartedWatchDogTimer"
QT_MOC_LITERAL(9, 256, 20), // "stoppedWatchDogTimer"
QT_MOC_LITERAL(10, 277, 17), // "microRosConnected"
QT_MOC_LITERAL(11, 295, 19), // "commandStateChanged"
QT_MOC_LITERAL(12, 315, 7), // "int64_t"
QT_MOC_LITERAL(13, 323, 2), // "id"
QT_MOC_LITERAL(14, 326, 5) // "state"

    },
    "NodeQThread\0motionStatusMsgChanged\0\0"
    "motion_status_msgs::msg::MotionStatus::SharedPtr\0"
    "serialMsgChanged\0std_msgs::msg::String::SharedPtr\0"
    "motionParamsServiceResponsed\0"
    "motion_params_service::srv::MotionParamsService::Response::SharedPtr\0"
    "restartedWatchDogTimer\0stoppedWatchDogTimer\0"
    "microRosConnected\0commandStateChanged\0"
    "int64_t\0id\0state"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_NodeQThread[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       7,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   49,    2, 0x06 /* Public */,
       4,    1,   52,    2, 0x06 /* Public */,
       6,    1,   55,    2, 0x06 /* Public */,
       8,    0,   58,    2, 0x06 /* Public */,
       9,    0,   59,    2, 0x06 /* Public */,
      10,    0,   60,    2, 0x06 /* Public */,
      11,    2,   61,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    2,
    QMetaType::Void, 0x80000000 | 5,    2,
    QMetaType::Void, 0x80000000 | 7,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 12, QMetaType::Int,   13,   14,

       0        // eod
};

void NodeQThread::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<NodeQThread *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->motionStatusMsgChanged((*reinterpret_cast< motion_status_msgs::msg::MotionStatus::SharedPtr(*)>(_a[1]))); break;
        case 1: _t->serialMsgChanged((*reinterpret_cast< std_msgs::msg::String::SharedPtr(*)>(_a[1]))); break;
        case 2: _t->motionParamsServiceResponsed((*reinterpret_cast< motion_params_service::srv::MotionParamsService::Response::SharedPtr(*)>(_a[1]))); break;
        case 3: _t->restartedWatchDogTimer(); break;
        case 4: _t->stoppedWatchDogTimer(); break;
        case 5: _t->microRosConnected(); break;
        case 6: _t->commandStateChanged((*reinterpret_cast< int64_t(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (NodeQThread::*)(motion_status_msgs::msg::MotionStatus::SharedPtr );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&NodeQThread::motionStatusMsgChanged)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (NodeQThread::*)(std_msgs::msg::String::SharedPtr );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&NodeQThread::serialMsgChanged)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (NodeQThread::*)(motion_params_service::srv::MotionParamsService::Response::SharedPtr );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&NodeQThread::motionParamsServiceResponsed)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (NodeQThread::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&NodeQThread::restartedWatchDogTimer)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (NodeQThread::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&NodeQThread::stoppedWatchDogTimer)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (NodeQThread::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&NodeQThread::microRosConnected)) {
                *result = 5;
                return;
            }
        }
        {
            using _t = void (NodeQThread::*)(int64_t , int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&NodeQThread::commandStateChanged)) {
                *result = 6;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject NodeQThread::staticMetaObject = { {
    QMetaObject::SuperData::link<QThread::staticMetaObject>(),
    qt_meta_stringdata_NodeQThread.data,
    qt_meta_data_NodeQThread,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *NodeQThread::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *NodeQThread::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_NodeQThread.stringdata0))
        return static_cast<void*>(this);
    return QThread::qt_metacast(_clname);
}

int NodeQThread::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QThread::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 7)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 7;
    }
    return _id;
}

// SIGNAL 0
void NodeQThread::motionStatusMsgChanged(motion_status_msgs::msg::MotionStatus::SharedPtr _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void NodeQThread::serialMsgChanged(std_msgs::msg::String::SharedPtr _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void NodeQThread::motionParamsServiceResponsed(motion_params_service::srv::MotionParamsService::Response::SharedPtr _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void NodeQThread::restartedWatchDogTimer()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}

// SIGNAL 4
void NodeQThread::stoppedWatchDogTimer()
{
    QMetaObject::activate(this, &staticMetaObject, 4, nullptr);
}

// SIGNAL 5
void NodeQThread::microRosConnected()
{
    QMetaObject::activate(this, &staticMetaObject, 5, nullptr);
}

// SIGNAL 6
void NodeQThread::commandStateChanged(int64_t _t1, int _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
