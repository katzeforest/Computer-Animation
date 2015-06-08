/****************************************************************************
** Meta object code from reading C++ file 'controlpaneldialog.h'
**
** Created: Sat Nov 29 12:07:20 2014
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../controlpaneldialog.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'controlpaneldialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_ControlPanelDialog[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
      34,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      20,   19,   19,   19, 0x08,
      50,   19,   19,   19, 0x08,
      79,   19,   19,   19, 0x08,
     108,   19,   19,   19, 0x08,
     139,   19,   19,   19, 0x08,
     171,   19,   19,   19, 0x08,
     205,   19,   19,   19, 0x08,
     235,   19,   19,   19, 0x08,
     270,   19,   19,   19, 0x08,
     303,   19,   19,   19, 0x08,
     337,   19,   19,   19, 0x08,
     368,   19,   19,   19, 0x08,
     406,  401,   19,   19, 0x08,
     437,   19,   19,   19, 0x08,
     477,   19,   19,   19, 0x08,
     517,   19,   19,   19, 0x08,
     554,   19,   19,   19, 0x08,
     592,   19,   19,   19, 0x08,
     625,   19,   19,   19, 0x08,
     661,   19,   19,   19, 0x08,
     694,   19,   19,   19, 0x08,
     733,   19,   19,   19, 0x08,
     769,   19,   19,   19, 0x08,
     800,   19,   19,   19, 0x08,
     836,   19,   19,   19, 0x08,
     870,   19,   19,   19, 0x08,
     905,   19,   19,   19, 0x08,
     940,   19,   19,   19, 0x08,
     974,   19,   19,   19, 0x08,
    1012,   19,   19,   19, 0x08,
    1047,   19,   19,   19, 0x08,
    1082,   19,   19,   19, 0x08,
    1119,   19,   19,   19, 0x08,
    1157,   19,   19,   19, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_ControlPanelDialog[] = {
    "ControlPanelDialog\0\0ControlPanelDialog_rejected()\0"
    "on_seekRadioButton_clicked()\0"
    "on_fleeRadioButton_clicked()\0"
    "on_wanderRadioButton_clicked()\0"
    "on_arrivalRadioButton_clicked()\0"
    "on_departureRadioButton_clicked()\0"
    "on_avoidRadioButton_clicked()\0"
    "on_separationRadioButton_clicked()\0"
    "on_flockingRadioButton_clicked()\0"
    "on_alignmentRadioButton_clicked()\0"
    "on_readerRadioButton_clicked()\0"
    "on_cohesionRadioButton_clicked()\0arg1\0"
    "on_debugMode_stateChanged(int)\0"
    "on_agentNumberSpinBox_editingFinished()\0"
    "on_maxVelocitySpinBox_editingFinished()\0"
    "on_maxForceSpinBox_editingFinished()\0"
    "on_maxTorqueSpinBox_editingFinished()\0"
    "on_massSpinBox_editingFinished()\0"
    "on_inertiaSpinBox_editingFinished()\0"
    "on_maxWSpinBox_editingFinished()\0"
    "on_velocityKvSpinBox_editingFinished()\0"
    "on_headingSpinBox_editingFinished()\0"
    "on_kpSpinBox_editingFinished()\0"
    "on_arrivalSpinBox_editingFinished()\0"
    "on_noiseSpinBox_editingFinished()\0"
    "on_kAvoidSpinBox_editingFinished()\0"
    "on_allginSpinBox_editingFinished()\0"
    "on_cohesSpinBox_editingFinished()\0"
    "on_departureSpinBox_editingFinished()\0"
    "on_wanderSpinBox_editingFinished()\0"
    "on_tAvoidSpinBox_editingFinished()\0"
    "on_separateSpinBox_editingFinished()\0"
    "on_rNeighborSpinBox_editingFinished()\0"
    "on_applyButton_clicked()\0"
};

const QMetaObject ControlPanelDialog::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_ControlPanelDialog,
      qt_meta_data_ControlPanelDialog, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &ControlPanelDialog::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *ControlPanelDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *ControlPanelDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ControlPanelDialog))
        return static_cast<void*>(const_cast< ControlPanelDialog*>(this));
    return QDialog::qt_metacast(_clname);
}

int ControlPanelDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: ControlPanelDialog_rejected(); break;
        case 1: on_seekRadioButton_clicked(); break;
        case 2: on_fleeRadioButton_clicked(); break;
        case 3: on_wanderRadioButton_clicked(); break;
        case 4: on_arrivalRadioButton_clicked(); break;
        case 5: on_departureRadioButton_clicked(); break;
        case 6: on_avoidRadioButton_clicked(); break;
        case 7: on_separationRadioButton_clicked(); break;
        case 8: on_flockingRadioButton_clicked(); break;
        case 9: on_alignmentRadioButton_clicked(); break;
        case 10: on_readerRadioButton_clicked(); break;
        case 11: on_cohesionRadioButton_clicked(); break;
        case 12: on_debugMode_stateChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 13: on_agentNumberSpinBox_editingFinished(); break;
        case 14: on_maxVelocitySpinBox_editingFinished(); break;
        case 15: on_maxForceSpinBox_editingFinished(); break;
        case 16: on_maxTorqueSpinBox_editingFinished(); break;
        case 17: on_massSpinBox_editingFinished(); break;
        case 18: on_inertiaSpinBox_editingFinished(); break;
        case 19: on_maxWSpinBox_editingFinished(); break;
        case 20: on_velocityKvSpinBox_editingFinished(); break;
        case 21: on_headingSpinBox_editingFinished(); break;
        case 22: on_kpSpinBox_editingFinished(); break;
        case 23: on_arrivalSpinBox_editingFinished(); break;
        case 24: on_noiseSpinBox_editingFinished(); break;
        case 25: on_kAvoidSpinBox_editingFinished(); break;
        case 26: on_allginSpinBox_editingFinished(); break;
        case 27: on_cohesSpinBox_editingFinished(); break;
        case 28: on_departureSpinBox_editingFinished(); break;
        case 29: on_wanderSpinBox_editingFinished(); break;
        case 30: on_tAvoidSpinBox_editingFinished(); break;
        case 31: on_separateSpinBox_editingFinished(); break;
        case 32: on_rNeighborSpinBox_editingFinished(); break;
        case 33: on_applyButton_clicked(); break;
        default: ;
        }
        _id -= 34;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
