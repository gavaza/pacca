/****************************************************************************
** Meta object code from reading C++ file 'ControlVideo.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.3.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../src/widgets/ControlVideo.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#include <QtCore/QList>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ControlVideo.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.3.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_VlcControlVideo_t {
    QByteArrayData data[13];
    char stringdata[176];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_VlcControlVideo_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_VlcControlVideo_t qt_meta_stringdata_VlcControlVideo = {
    {
QT_MOC_LITERAL(0, 0, 15),
QT_MOC_LITERAL(1, 16, 7),
QT_MOC_LITERAL(2, 24, 0),
QT_MOC_LITERAL(3, 25, 15),
QT_MOC_LITERAL(4, 41, 16),
QT_MOC_LITERAL(5, 58, 14),
QT_MOC_LITERAL(6, 73, 11),
QT_MOC_LITERAL(7, 85, 12),
QT_MOC_LITERAL(8, 98, 8),
QT_MOC_LITERAL(9, 107, 21),
QT_MOC_LITERAL(10, 129, 15),
QT_MOC_LITERAL(11, 145, 18),
QT_MOC_LITERAL(12, 164, 11)
    },
    "VlcControlVideo\0actions\0\0QList<QAction*>\0"
    "Vlc::ActionsType\0subtitleTracks\0"
    "videoTracks\0loadSubtitle\0subtitle\0"
    "updateSubtitleActions\0updateSubtitles\0"
    "updateVideoActions\0updateVideo"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_VlcControlVideo[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,   54,    2, 0x06 /* Public */,
       5,    1,   59,    2, 0x06 /* Public */,
       6,    1,   62,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       7,    1,   65,    2, 0x0a /* Public */,
       9,    0,   68,    2, 0x08 /* Private */,
      10,    0,   69,    2, 0x08 /* Private */,
      11,    0,   70,    2, 0x08 /* Private */,
      12,    0,   71,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3, 0x80000000 | 4,    2,    2,
    QMetaType::Void, 0x80000000 | 3,    2,
    QMetaType::Void, 0x80000000 | 3,    2,

 // slots: parameters
    QMetaType::Void, QMetaType::QString,    8,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void VlcControlVideo::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        VlcControlVideo *_t = static_cast<VlcControlVideo *>(_o);
        switch (_id) {
        case 0: _t->actions((*reinterpret_cast< QList<QAction*>(*)>(_a[1])),(*reinterpret_cast< const Vlc::ActionsType(*)>(_a[2]))); break;
        case 1: _t->subtitleTracks((*reinterpret_cast< QList<QAction*>(*)>(_a[1]))); break;
        case 2: _t->videoTracks((*reinterpret_cast< QList<QAction*>(*)>(_a[1]))); break;
        case 3: _t->loadSubtitle((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 4: _t->updateSubtitleActions(); break;
        case 5: _t->updateSubtitles(); break;
        case 6: _t->updateVideoActions(); break;
        case 7: _t->updateVideo(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (VlcControlVideo::*_t)(QList<QAction*> , const Vlc::ActionsType );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&VlcControlVideo::actions)) {
                *result = 0;
            }
        }
        {
            typedef void (VlcControlVideo::*_t)(QList<QAction*> );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&VlcControlVideo::subtitleTracks)) {
                *result = 1;
            }
        }
        {
            typedef void (VlcControlVideo::*_t)(QList<QAction*> );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&VlcControlVideo::videoTracks)) {
                *result = 2;
            }
        }
    }
}

const QMetaObject VlcControlVideo::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_VlcControlVideo.data,
      qt_meta_data_VlcControlVideo,  qt_static_metacall, 0, 0}
};


const QMetaObject *VlcControlVideo::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *VlcControlVideo::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_VlcControlVideo.stringdata))
        return static_cast<void*>(const_cast< VlcControlVideo*>(this));
    return QObject::qt_metacast(_clname);
}

int VlcControlVideo::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 8)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 8;
    }
    return _id;
}

// SIGNAL 0
void VlcControlVideo::actions(QList<QAction*> _t1, const Vlc::ActionsType _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void VlcControlVideo::subtitleTracks(QList<QAction*> _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void VlcControlVideo::videoTracks(QList<QAction*> _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_END_MOC_NAMESPACE
