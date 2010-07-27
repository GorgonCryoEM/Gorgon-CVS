# -*- coding: utf-8 -*-

# Form implementation generated from reading ui file 'ui_dialog_calpha_flexible_fitting.ui'
#
# Created: Tue Jul 27 16:08:42 2010
#      by: PyQt4 UI code generator 4.4.3
#
# WARNING! All changes made in this file will be lost!

from PyQt4 import QtCore, QtGui

class Ui_DialogCAlphaFlexibleFitting(object):
    def setupUi(self, DialogCAlphaFlexibleFitting):
        DialogCAlphaFlexibleFitting.setObjectName("DialogCAlphaFlexibleFitting")
        DialogCAlphaFlexibleFitting.resize(405, 605)
        sizePolicy = QtGui.QSizePolicy(QtGui.QSizePolicy.MinimumExpanding, QtGui.QSizePolicy.MinimumExpanding)
        sizePolicy.setHorizontalStretch(0)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(DialogCAlphaFlexibleFitting.sizePolicy().hasHeightForWidth())
        DialogCAlphaFlexibleFitting.setSizePolicy(sizePolicy)
        DialogCAlphaFlexibleFitting.setMinimumSize(QtCore.QSize(270, 296))
        self.verticalLayout_3 = QtGui.QVBoxLayout(DialogCAlphaFlexibleFitting)
        self.verticalLayout_3.setObjectName("verticalLayout_3")
        self.horizontalLayout = QtGui.QHBoxLayout()
        self.horizontalLayout.setObjectName("horizontalLayout")
        self.pushButtonLoadHelices = QtGui.QPushButton(DialogCAlphaFlexibleFitting)
        self.pushButtonLoadHelices.setObjectName("pushButtonLoadHelices")
        self.horizontalLayout.addWidget(self.pushButtonLoadHelices)
        self.pushButtonLoadCAlpha = QtGui.QPushButton(DialogCAlphaFlexibleFitting)
        self.pushButtonLoadCAlpha.setObjectName("pushButtonLoadCAlpha")
        self.horizontalLayout.addWidget(self.pushButtonLoadCAlpha)
        self.verticalLayout_3.addLayout(self.horizontalLayout)
        self.tabWidget = QtGui.QTabWidget(DialogCAlphaFlexibleFitting)
        self.tabWidget.setObjectName("tabWidget")
        self.tabRigid = QtGui.QWidget()
        self.tabRigid.setObjectName("tabRigid")
        self.verticalLayout_6 = QtGui.QVBoxLayout(self.tabRigid)
        self.verticalLayout_6.setObjectName("verticalLayout_6")
        self.horizontalLayout_8 = QtGui.QHBoxLayout()
        self.horizontalLayout_8.setObjectName("horizontalLayout_8")
        self.labelCandidateCount = QtGui.QLabel(self.tabRigid)
        self.labelCandidateCount.setObjectName("labelCandidateCount")
        self.horizontalLayout_8.addWidget(self.labelCandidateCount)
        self.spinBoxMaxAlignments = QtGui.QSpinBox(self.tabRigid)
        self.spinBoxMaxAlignments.setMinimum(1)
        self.spinBoxMaxAlignments.setMaximum(100)
        self.spinBoxMaxAlignments.setProperty("value", QtCore.QVariant(5))
        self.spinBoxMaxAlignments.setObjectName("spinBoxMaxAlignments")
        self.horizontalLayout_8.addWidget(self.spinBoxMaxAlignments)
        self.verticalLayout_6.addLayout(self.horizontalLayout_8)
        self.groupBoxAdvancedSettings = QtGui.QGroupBox(self.tabRigid)
        self.groupBoxAdvancedSettings.setObjectName("groupBoxAdvancedSettings")
        self.formLayout_3 = QtGui.QFormLayout(self.groupBoxAdvancedSettings)
        self.formLayout_3.setFieldGrowthPolicy(QtGui.QFormLayout.AllNonFixedFieldsGrow)
        self.formLayout_3.setObjectName("formLayout_3")
        self.labelJointAngleThreshold_4 = QtGui.QLabel(self.groupBoxAdvancedSettings)
        self.labelJointAngleThreshold_4.setObjectName("labelJointAngleThreshold_4")
        self.formLayout_3.setWidget(0, QtGui.QFormLayout.LabelRole, self.labelJointAngleThreshold_4)
        self.spinBoxJointAngleThreshold = QtGui.QSpinBox(self.groupBoxAdvancedSettings)
        self.spinBoxJointAngleThreshold.setMaximum(180)
        self.spinBoxJointAngleThreshold.setProperty("value", QtCore.QVariant(30))
        self.spinBoxJointAngleThreshold.setObjectName("spinBoxJointAngleThreshold")
        self.formLayout_3.setWidget(0, QtGui.QFormLayout.FieldRole, self.spinBoxJointAngleThreshold)
        self.labelJointAngleThreshold_3 = QtGui.QLabel(self.groupBoxAdvancedSettings)
        self.labelJointAngleThreshold_3.setObjectName("labelJointAngleThreshold_3")
        self.formLayout_3.setWidget(1, QtGui.QFormLayout.LabelRole, self.labelJointAngleThreshold_3)
        self.spinBoxDihedralAngleThreshold = QtGui.QSpinBox(self.groupBoxAdvancedSettings)
        self.spinBoxDihedralAngleThreshold.setMaximum(180)
        self.spinBoxDihedralAngleThreshold.setProperty("value", QtCore.QVariant(30))
        self.spinBoxDihedralAngleThreshold.setObjectName("spinBoxDihedralAngleThreshold")
        self.formLayout_3.setWidget(1, QtGui.QFormLayout.FieldRole, self.spinBoxDihedralAngleThreshold)
        self.labelJointAngleThreshold_2 = QtGui.QLabel(self.groupBoxAdvancedSettings)
        self.labelJointAngleThreshold_2.setObjectName("labelJointAngleThreshold_2")
        self.formLayout_3.setWidget(2, QtGui.QFormLayout.LabelRole, self.labelJointAngleThreshold_2)
        self.spinBoxHelixLengthThreshold = QtGui.QSpinBox(self.groupBoxAdvancedSettings)
        self.spinBoxHelixLengthThreshold.setMaximum(50)
        self.spinBoxHelixLengthThreshold.setProperty("value", QtCore.QVariant(10))
        self.spinBoxHelixLengthThreshold.setObjectName("spinBoxHelixLengthThreshold")
        self.formLayout_3.setWidget(2, QtGui.QFormLayout.FieldRole, self.spinBoxHelixLengthThreshold)
        self.labelJointAngleThreshold = QtGui.QLabel(self.groupBoxAdvancedSettings)
        self.labelJointAngleThreshold.setObjectName("labelJointAngleThreshold")
        self.formLayout_3.setWidget(3, QtGui.QFormLayout.LabelRole, self.labelJointAngleThreshold)
        self.spinBoxHelixCentroidThreshold = QtGui.QSpinBox(self.groupBoxAdvancedSettings)
        self.spinBoxHelixCentroidThreshold.setMaximum(50)
        self.spinBoxHelixCentroidThreshold.setProperty("value", QtCore.QVariant(5))
        self.spinBoxHelixCentroidThreshold.setObjectName("spinBoxHelixCentroidThreshold")
        self.formLayout_3.setWidget(3, QtGui.QFormLayout.FieldRole, self.spinBoxHelixCentroidThreshold)
        self.verticalLayout_6.addWidget(self.groupBoxAdvancedSettings)
        self.horizontalLayout_3 = QtGui.QHBoxLayout()
        self.horizontalLayout_3.setObjectName("horizontalLayout_3")
        spacerItem = QtGui.QSpacerItem(358, 20, QtGui.QSizePolicy.Expanding, QtGui.QSizePolicy.Minimum)
        self.horizontalLayout_3.addItem(spacerItem)
        self.pushButtonReset = QtGui.QPushButton(self.tabRigid)
        self.pushButtonReset.setObjectName("pushButtonReset")
        self.horizontalLayout_3.addWidget(self.pushButtonReset)
        self.pushButtonOk = QtGui.QPushButton(self.tabRigid)
        self.pushButtonOk.setObjectName("pushButtonOk")
        self.horizontalLayout_3.addWidget(self.pushButtonOk)
        self.verticalLayout_6.addLayout(self.horizontalLayout_3)
        spacerItem1 = QtGui.QSpacerItem(20, 40, QtGui.QSizePolicy.Minimum, QtGui.QSizePolicy.Expanding)
        self.verticalLayout_6.addItem(spacerItem1)
        self.tabWidget.addTab(self.tabRigid, "")
        self.tabAlignments = QtGui.QWidget()
        self.tabAlignments.setObjectName("tabAlignments")
        self.verticalLayout_2 = QtGui.QVBoxLayout(self.tabAlignments)
        self.verticalLayout_2.setObjectName("verticalLayout_2")
        self.horizontalLayout_5 = QtGui.QHBoxLayout()
        self.horizontalLayout_5.setObjectName("horizontalLayout_5")
        self.labelAlignment = QtGui.QLabel(self.tabAlignments)
        self.labelAlignment.setObjectName("labelAlignment")
        self.horizontalLayout_5.addWidget(self.labelAlignment)
        self.comboBoxAlignment = QtGui.QComboBox(self.tabAlignments)
        self.comboBoxAlignment.setObjectName("comboBoxAlignment")
        self.horizontalLayout_5.addWidget(self.comboBoxAlignment)
        self.verticalLayout_2.addLayout(self.horizontalLayout_5)
        self.tableWidget = QtGui.QTableWidget(self.tabAlignments)
        self.tableWidget.setObjectName("tableWidget")
        self.tableWidget.setColumnCount(3)
        self.tableWidget.setRowCount(0)
        item = QtGui.QTableWidgetItem()
        self.tableWidget.setHorizontalHeaderItem(0, item)
        item = QtGui.QTableWidgetItem()
        self.tableWidget.setHorizontalHeaderItem(1, item)
        item = QtGui.QTableWidgetItem()
        self.tableWidget.setHorizontalHeaderItem(2, item)
        self.verticalLayout_2.addWidget(self.tableWidget)
        self.widget_2 = QtGui.QWidget(self.tabAlignments)
        self.widget_2.setObjectName("widget_2")
        self.horizontalLayout_4 = QtGui.QHBoxLayout(self.widget_2)
        self.horizontalLayout_4.setObjectName("horizontalLayout_4")
        self.label_2 = QtGui.QLabel(self.widget_2)
        self.label_2.setObjectName("label_2")
        self.horizontalLayout_4.addWidget(self.label_2)
        self.comboBoxCluster = QtGui.QComboBox(self.widget_2)
        self.comboBoxCluster.setObjectName("comboBoxCluster")
        self.horizontalLayout_4.addWidget(self.comboBoxCluster)
        self.verticalLayout_2.addWidget(self.widget_2)
        self.groupBoxHelixMatching = QtGui.QGroupBox(self.tabAlignments)
        self.groupBoxHelixMatching.setObjectName("groupBoxHelixMatching")
        self.verticalLayout_4 = QtGui.QVBoxLayout(self.groupBoxHelixMatching)
        self.verticalLayout_4.setObjectName("verticalLayout_4")
        self.label = QtGui.QLabel(self.groupBoxHelixMatching)
        self.label.setLineWidth(2)
        self.label.setWordWrap(True)
        self.label.setObjectName("label")
        self.verticalLayout_4.addWidget(self.label)
        self.horizontalLayout_6 = QtGui.QHBoxLayout()
        self.horizontalLayout_6.setObjectName("horizontalLayout_6")
        spacerItem2 = QtGui.QSpacerItem(40, 20, QtGui.QSizePolicy.Expanding, QtGui.QSizePolicy.Minimum)
        self.horizontalLayout_6.addItem(spacerItem2)
        self.pushButtonMatchHelices = QtGui.QPushButton(self.groupBoxHelixMatching)
        self.pushButtonMatchHelices.setObjectName("pushButtonMatchHelices")
        self.horizontalLayout_6.addWidget(self.pushButtonMatchHelices)
        self.verticalLayout_4.addLayout(self.horizontalLayout_6)
        self.verticalLayout_2.addWidget(self.groupBoxHelixMatching)
        self.groupBoxClusterMerging = QtGui.QGroupBox(self.tabAlignments)
        self.groupBoxClusterMerging.setObjectName("groupBoxClusterMerging")
        self.gridLayout = QtGui.QGridLayout(self.groupBoxClusterMerging)
        self.gridLayout.setObjectName("gridLayout")
        self.label_3 = QtGui.QLabel(self.groupBoxClusterMerging)
        self.label_3.setObjectName("label_3")
        self.gridLayout.addWidget(self.label_3, 0, 0, 1, 1)
        self.comboBoxMerge1 = QtGui.QComboBox(self.groupBoxClusterMerging)
        self.comboBoxMerge1.setObjectName("comboBoxMerge1")
        self.gridLayout.addWidget(self.comboBoxMerge1, 0, 1, 1, 1)
        self.label_4 = QtGui.QLabel(self.groupBoxClusterMerging)
        self.label_4.setObjectName("label_4")
        self.gridLayout.addWidget(self.label_4, 1, 0, 1, 1)
        self.comboBoxMerge2 = QtGui.QComboBox(self.groupBoxClusterMerging)
        self.comboBoxMerge2.setObjectName("comboBoxMerge2")
        self.gridLayout.addWidget(self.comboBoxMerge2, 1, 1, 1, 1)
        self.horizontalLayout_7 = QtGui.QHBoxLayout()
        self.horizontalLayout_7.setObjectName("horizontalLayout_7")
        spacerItem3 = QtGui.QSpacerItem(40, 20, QtGui.QSizePolicy.Expanding, QtGui.QSizePolicy.Minimum)
        self.horizontalLayout_7.addItem(spacerItem3)
        self.pushButtonMergeClusters = QtGui.QPushButton(self.groupBoxClusterMerging)
        self.pushButtonMergeClusters.setObjectName("pushButtonMergeClusters")
        self.horizontalLayout_7.addWidget(self.pushButtonMergeClusters)
        self.gridLayout.addLayout(self.horizontalLayout_7, 2, 0, 1, 2)
        self.verticalLayout_2.addWidget(self.groupBoxClusterMerging)
        spacerItem4 = QtGui.QSpacerItem(20, 40, QtGui.QSizePolicy.Minimum, QtGui.QSizePolicy.Expanding)
        self.verticalLayout_2.addItem(spacerItem4)
        self.tabWidget.addTab(self.tabAlignments, "")
        self.tabFlexibleFit = QtGui.QWidget()
        self.tabFlexibleFit.setObjectName("tabFlexibleFit")
        self.verticalLayout = QtGui.QVBoxLayout(self.tabFlexibleFit)
        self.verticalLayout.setObjectName("verticalLayout")
        self.horizontalLayout_2 = QtGui.QHBoxLayout()
        self.horizontalLayout_2.setObjectName("horizontalLayout_2")
        self.radioButtonFlexibleFitting = QtGui.QRadioButton(self.tabFlexibleFit)
        self.radioButtonFlexibleFitting.setChecked(True)
        self.radioButtonFlexibleFitting.setObjectName("radioButtonFlexibleFitting")
        self.horizontalLayout_2.addWidget(self.radioButtonFlexibleFitting)
        self.radioButtonInterpolation = QtGui.QRadioButton(self.tabFlexibleFit)
        self.radioButtonInterpolation.setObjectName("radioButtonInterpolation")
        self.horizontalLayout_2.addWidget(self.radioButtonInterpolation)
        self.verticalLayout.addLayout(self.horizontalLayout_2)
        self.groupBoxFlexibleSettings = QtGui.QGroupBox(self.tabFlexibleFit)
        self.groupBoxFlexibleSettings.setObjectName("groupBoxFlexibleSettings")
        self.verticalLayout_7 = QtGui.QVBoxLayout(self.groupBoxFlexibleSettings)
        self.verticalLayout_7.setObjectName("verticalLayout_7")
        self.flexibleSettings = QtGui.QFormLayout()
        self.flexibleSettings.setFieldGrowthPolicy(QtGui.QFormLayout.AllNonFixedFieldsGrow)
        self.flexibleSettings.setObjectName("flexibleSettings")
        self.useSoftHandlesCheckBox = QtGui.QCheckBox(self.groupBoxFlexibleSettings)
        self.useSoftHandlesCheckBox.setChecked(True)
        self.useSoftHandlesCheckBox.setTristate(False)
        self.useSoftHandlesCheckBox.setObjectName("useSoftHandlesCheckBox")
        self.flexibleSettings.setWidget(0, QtGui.QFormLayout.FieldRole, self.useSoftHandlesCheckBox)
        self.doRigidInitializationLabel = QtGui.QLabel(self.groupBoxFlexibleSettings)
        self.doRigidInitializationLabel.setObjectName("doRigidInitializationLabel")
        self.flexibleSettings.setWidget(1, QtGui.QFormLayout.LabelRole, self.doRigidInitializationLabel)
        self.doRigidInitializationCheckBox = QtGui.QCheckBox(self.groupBoxFlexibleSettings)
        self.doRigidInitializationCheckBox.setChecked(True)
        self.doRigidInitializationCheckBox.setObjectName("doRigidInitializationCheckBox")
        self.flexibleSettings.setWidget(1, QtGui.QFormLayout.FieldRole, self.doRigidInitializationCheckBox)
        self.neighborhoodSizeLabel = QtGui.QLabel(self.groupBoxFlexibleSettings)
        self.neighborhoodSizeLabel.setObjectName("neighborhoodSizeLabel")
        self.flexibleSettings.setWidget(2, QtGui.QFormLayout.LabelRole, self.neighborhoodSizeLabel)
        self.neighborhoodSizeSpinBox = QtGui.QSpinBox(self.groupBoxFlexibleSettings)
        self.neighborhoodSizeSpinBox.setMinimum(2)
        self.neighborhoodSizeSpinBox.setProperty("value", QtCore.QVariant(3))
        self.neighborhoodSizeSpinBox.setObjectName("neighborhoodSizeSpinBox")
        self.flexibleSettings.setWidget(2, QtGui.QFormLayout.FieldRole, self.neighborhoodSizeSpinBox)
        self.laplacianWeightLabel = QtGui.QLabel(self.groupBoxFlexibleSettings)
        self.laplacianWeightLabel.setObjectName("laplacianWeightLabel")
        self.flexibleSettings.setWidget(3, QtGui.QFormLayout.LabelRole, self.laplacianWeightLabel)
        self.laplacianWeightDoubleSpinBox = QtGui.QDoubleSpinBox(self.groupBoxFlexibleSettings)
        self.laplacianWeightDoubleSpinBox.setMaximum(2.0)
        self.laplacianWeightDoubleSpinBox.setSingleStep(0.01)
        self.laplacianWeightDoubleSpinBox.setProperty("value", QtCore.QVariant(1.0))
        self.laplacianWeightDoubleSpinBox.setObjectName("laplacianWeightDoubleSpinBox")
        self.flexibleSettings.setWidget(3, QtGui.QFormLayout.FieldRole, self.laplacianWeightDoubleSpinBox)
        self.hardHandleWeightLabel = QtGui.QLabel(self.groupBoxFlexibleSettings)
        self.hardHandleWeightLabel.setObjectName("hardHandleWeightLabel")
        self.flexibleSettings.setWidget(4, QtGui.QFormLayout.LabelRole, self.hardHandleWeightLabel)
        self.hardHandleWeightDoubleSpinBox = QtGui.QDoubleSpinBox(self.groupBoxFlexibleSettings)
        self.hardHandleWeightDoubleSpinBox.setMaximum(2.0)
        self.hardHandleWeightDoubleSpinBox.setSingleStep(0.01)
        self.hardHandleWeightDoubleSpinBox.setProperty("value", QtCore.QVariant(1.0))
        self.hardHandleWeightDoubleSpinBox.setObjectName("hardHandleWeightDoubleSpinBox")
        self.flexibleSettings.setWidget(4, QtGui.QFormLayout.FieldRole, self.hardHandleWeightDoubleSpinBox)
        self.softHandleWeightLabel = QtGui.QLabel(self.groupBoxFlexibleSettings)
        self.softHandleWeightLabel.setObjectName("softHandleWeightLabel")
        self.flexibleSettings.setWidget(5, QtGui.QFormLayout.LabelRole, self.softHandleWeightLabel)
        self.softHandleWeightDoubleSpinBox = QtGui.QDoubleSpinBox(self.groupBoxFlexibleSettings)
        self.softHandleWeightDoubleSpinBox.setMaximum(2.0)
        self.softHandleWeightDoubleSpinBox.setSingleStep(0.01)
        self.softHandleWeightDoubleSpinBox.setProperty("value", QtCore.QVariant(0.05))
        self.softHandleWeightDoubleSpinBox.setObjectName("softHandleWeightDoubleSpinBox")
        self.flexibleSettings.setWidget(5, QtGui.QFormLayout.FieldRole, self.softHandleWeightDoubleSpinBox)
        self.useSoftHandlesLabel = QtGui.QLabel(self.groupBoxFlexibleSettings)
        self.useSoftHandlesLabel.setObjectName("useSoftHandlesLabel")
        self.flexibleSettings.setWidget(0, QtGui.QFormLayout.LabelRole, self.useSoftHandlesLabel)
        self.verticalLayout_7.addLayout(self.flexibleSettings)
        self.verticalLayout.addWidget(self.groupBoxFlexibleSettings)
        self.widget = QtGui.QWidget(self.tabFlexibleFit)
        self.widget.setObjectName("widget")
        self.horizontalLayout_15 = QtGui.QHBoxLayout(self.widget)
        self.horizontalLayout_15.setObjectName("horizontalLayout_15")
        spacerItem5 = QtGui.QSpacerItem(40, 20, QtGui.QSizePolicy.Expanding, QtGui.QSizePolicy.Minimum)
        self.horizontalLayout_15.addItem(spacerItem5)
        self.pushButtonRunFlexible = QtGui.QPushButton(self.widget)
        self.pushButtonRunFlexible.setObjectName("pushButtonRunFlexible")
        self.horizontalLayout_15.addWidget(self.pushButtonRunFlexible)
        self.verticalLayout.addWidget(self.widget)
        spacerItem6 = QtGui.QSpacerItem(20, 40, QtGui.QSizePolicy.Minimum, QtGui.QSizePolicy.Expanding)
        self.verticalLayout.addItem(spacerItem6)
        self.tabWidget.addTab(self.tabFlexibleFit, "")
        self.verticalLayout_3.addWidget(self.tabWidget)

        self.retranslateUi(DialogCAlphaFlexibleFitting)
        self.tabWidget.setCurrentIndex(0)
        QtCore.QObject.connect(self.pushButtonOk, QtCore.SIGNAL("clicked()"), DialogCAlphaFlexibleFitting.accept)
        QtCore.QObject.connect(self.pushButtonReset, QtCore.SIGNAL("clicked()"), DialogCAlphaFlexibleFitting.reject)
        QtCore.QMetaObject.connectSlotsByName(DialogCAlphaFlexibleFitting)
        DialogCAlphaFlexibleFitting.setTabOrder(self.pushButtonLoadHelices, self.pushButtonLoadCAlpha)
        DialogCAlphaFlexibleFitting.setTabOrder(self.pushButtonLoadCAlpha, self.tabWidget)
        DialogCAlphaFlexibleFitting.setTabOrder(self.tabWidget, self.spinBoxMaxAlignments)
        DialogCAlphaFlexibleFitting.setTabOrder(self.spinBoxMaxAlignments, self.spinBoxJointAngleThreshold)
        DialogCAlphaFlexibleFitting.setTabOrder(self.spinBoxJointAngleThreshold, self.spinBoxDihedralAngleThreshold)
        DialogCAlphaFlexibleFitting.setTabOrder(self.spinBoxDihedralAngleThreshold, self.spinBoxHelixLengthThreshold)
        DialogCAlphaFlexibleFitting.setTabOrder(self.spinBoxHelixLengthThreshold, self.spinBoxHelixCentroidThreshold)
        DialogCAlphaFlexibleFitting.setTabOrder(self.spinBoxHelixCentroidThreshold, self.pushButtonReset)
        DialogCAlphaFlexibleFitting.setTabOrder(self.pushButtonReset, self.pushButtonOk)
        DialogCAlphaFlexibleFitting.setTabOrder(self.pushButtonOk, self.comboBoxAlignment)
        DialogCAlphaFlexibleFitting.setTabOrder(self.comboBoxAlignment, self.tableWidget)
        DialogCAlphaFlexibleFitting.setTabOrder(self.tableWidget, self.comboBoxCluster)
        DialogCAlphaFlexibleFitting.setTabOrder(self.comboBoxCluster, self.pushButtonMatchHelices)
        DialogCAlphaFlexibleFitting.setTabOrder(self.pushButtonMatchHelices, self.radioButtonFlexibleFitting)
        DialogCAlphaFlexibleFitting.setTabOrder(self.radioButtonFlexibleFitting, self.radioButtonInterpolation)
        DialogCAlphaFlexibleFitting.setTabOrder(self.radioButtonInterpolation, self.useSoftHandlesCheckBox)
        DialogCAlphaFlexibleFitting.setTabOrder(self.useSoftHandlesCheckBox, self.doRigidInitializationCheckBox)
        DialogCAlphaFlexibleFitting.setTabOrder(self.doRigidInitializationCheckBox, self.neighborhoodSizeSpinBox)
        DialogCAlphaFlexibleFitting.setTabOrder(self.neighborhoodSizeSpinBox, self.laplacianWeightDoubleSpinBox)
        DialogCAlphaFlexibleFitting.setTabOrder(self.laplacianWeightDoubleSpinBox, self.hardHandleWeightDoubleSpinBox)
        DialogCAlphaFlexibleFitting.setTabOrder(self.hardHandleWeightDoubleSpinBox, self.softHandleWeightDoubleSpinBox)
        DialogCAlphaFlexibleFitting.setTabOrder(self.softHandleWeightDoubleSpinBox, self.pushButtonRunFlexible)

    def retranslateUi(self, DialogCAlphaFlexibleFitting):
        DialogCAlphaFlexibleFitting.setWindowTitle(QtGui.QApplication.translate("DialogCAlphaFlexibleFitting", "Align backbone to Density", None, QtGui.QApplication.UnicodeUTF8))
        self.pushButtonLoadHelices.setToolTip(QtGui.QApplication.translate("DialogCAlphaFlexibleFitting", "Load helix annotations into Gorgon", None, QtGui.QApplication.UnicodeUTF8))
        self.pushButtonLoadHelices.setText(QtGui.QApplication.translate("DialogCAlphaFlexibleFitting", "Load Helices", None, QtGui.QApplication.UnicodeUTF8))
        self.pushButtonLoadCAlpha.setToolTip(QtGui.QApplication.translate("DialogCAlphaFlexibleFitting", "Load the CAlpha backbone to Gorgon", None, QtGui.QApplication.UnicodeUTF8))
        self.pushButtonLoadCAlpha.setText(QtGui.QApplication.translate("DialogCAlphaFlexibleFitting", "Load PDB Structure", None, QtGui.QApplication.UnicodeUTF8))
        self.labelCandidateCount.setToolTip(QtGui.QApplication.translate("DialogCAlphaFlexibleFitting", "Maximum dihedral angle between helices that are being aligned", None, QtGui.QApplication.UnicodeUTF8))
        self.labelCandidateCount.setText(QtGui.QApplication.translate("DialogCAlphaFlexibleFitting", "Max alignments:", None, QtGui.QApplication.UnicodeUTF8))
        self.spinBoxMaxAlignments.setToolTip(QtGui.QApplication.translate("DialogCAlphaFlexibleFitting", "Maximum difference between centroids of helices being aligned", None, QtGui.QApplication.UnicodeUTF8))
        self.groupBoxAdvancedSettings.setTitle(QtGui.QApplication.translate("DialogCAlphaFlexibleFitting", "Rigidity Thresholds:", None, QtGui.QApplication.UnicodeUTF8))
        self.labelJointAngleThreshold_4.setText(QtGui.QApplication.translate("DialogCAlphaFlexibleFitting", "Joint Angle Difference:", None, QtGui.QApplication.UnicodeUTF8))
        self.spinBoxJointAngleThreshold.setToolTip(QtGui.QApplication.translate("DialogCAlphaFlexibleFitting", "Maximum joint angle difference between helices that are being aligned", None, QtGui.QApplication.UnicodeUTF8))
        self.spinBoxJointAngleThreshold.setSuffix(QtGui.QApplication.translate("DialogCAlphaFlexibleFitting", "°", None, QtGui.QApplication.UnicodeUTF8))
        self.labelJointAngleThreshold_3.setText(QtGui.QApplication.translate("DialogCAlphaFlexibleFitting", "Dihedral Angle Difference:", None, QtGui.QApplication.UnicodeUTF8))
        self.spinBoxDihedralAngleThreshold.setToolTip(QtGui.QApplication.translate("DialogCAlphaFlexibleFitting", "Maximum dihedral angle difference between helices that are being aligned", None, QtGui.QApplication.UnicodeUTF8))
        self.spinBoxDihedralAngleThreshold.setSuffix(QtGui.QApplication.translate("DialogCAlphaFlexibleFitting", "°", None, QtGui.QApplication.UnicodeUTF8))
        self.labelJointAngleThreshold_2.setText(QtGui.QApplication.translate("DialogCAlphaFlexibleFitting", "Helix Length Difference:", None, QtGui.QApplication.UnicodeUTF8))
        self.spinBoxHelixLengthThreshold.setToolTip(QtGui.QApplication.translate("DialogCAlphaFlexibleFitting", "Maximum difference of lengths of helices that are being aligned", None, QtGui.QApplication.UnicodeUTF8))
        self.spinBoxHelixLengthThreshold.setSuffix(QtGui.QApplication.translate("DialogCAlphaFlexibleFitting", " Å", None, QtGui.QApplication.UnicodeUTF8))
        self.labelJointAngleThreshold.setToolTip(QtGui.QApplication.translate("DialogCAlphaFlexibleFitting", "Maximum dihedral angle between helices that are being aligned", None, QtGui.QApplication.UnicodeUTF8))
        self.labelJointAngleThreshold.setText(QtGui.QApplication.translate("DialogCAlphaFlexibleFitting", "Helix Centroid Difference:", None, QtGui.QApplication.UnicodeUTF8))
        self.spinBoxHelixCentroidThreshold.setToolTip(QtGui.QApplication.translate("DialogCAlphaFlexibleFitting", "Maximum difference between centroids of helices being aligned", None, QtGui.QApplication.UnicodeUTF8))
        self.spinBoxHelixCentroidThreshold.setSuffix(QtGui.QApplication.translate("DialogCAlphaFlexibleFitting", " Å", None, QtGui.QApplication.UnicodeUTF8))
        self.pushButtonReset.setText(QtGui.QApplication.translate("DialogCAlphaFlexibleFitting", "Reset", None, QtGui.QApplication.UnicodeUTF8))
        self.pushButtonOk.setText(QtGui.QApplication.translate("DialogCAlphaFlexibleFitting", "Ok", None, QtGui.QApplication.UnicodeUTF8))
        self.tabWidget.setTabText(self.tabWidget.indexOf(self.tabRigid), QtGui.QApplication.translate("DialogCAlphaFlexibleFitting", "Rigid Fit", None, QtGui.QApplication.UnicodeUTF8))
        self.labelAlignment.setText(QtGui.QApplication.translate("DialogCAlphaFlexibleFitting", "Alignment:", None, QtGui.QApplication.UnicodeUTF8))
        self.tableWidget.horizontalHeaderItem(0).setText(QtGui.QApplication.translate("DialogCAlphaFlexibleFitting", "Cluster", None, QtGui.QApplication.UnicodeUTF8))
        self.tableWidget.horizontalHeaderItem(1).setText(QtGui.QApplication.translate("DialogCAlphaFlexibleFitting", "SSE Helix", None, QtGui.QApplication.UnicodeUTF8))
        self.tableWidget.horizontalHeaderItem(2).setText(QtGui.QApplication.translate("DialogCAlphaFlexibleFitting", "PDB Helix", None, QtGui.QApplication.UnicodeUTF8))
        self.label_2.setText(QtGui.QApplication.translate("DialogCAlphaFlexibleFitting", "Align to Cluster:", None, QtGui.QApplication.UnicodeUTF8))
        self.groupBoxHelixMatching.setTitle(QtGui.QApplication.translate("DialogCAlphaFlexibleFitting", "Helix Matching:", None, QtGui.QApplication.UnicodeUTF8))
        self.label.setText(QtGui.QApplication.translate("DialogCAlphaFlexibleFitting", "Select one PDB Ribbon Helix and one SSE Cylinder Helix in order to pair them as a cluster.  ", None, QtGui.QApplication.UnicodeUTF8))
        self.pushButtonMatchHelices.setText(QtGui.QApplication.translate("DialogCAlphaFlexibleFitting", "Match Helices", None, QtGui.QApplication.UnicodeUTF8))
        self.groupBoxClusterMerging.setTitle(QtGui.QApplication.translate("DialogCAlphaFlexibleFitting", "Merge Clusters:", None, QtGui.QApplication.UnicodeUTF8))
        self.label_3.setText(QtGui.QApplication.translate("DialogCAlphaFlexibleFitting", "Cluster 1: ", None, QtGui.QApplication.UnicodeUTF8))
        self.label_4.setText(QtGui.QApplication.translate("DialogCAlphaFlexibleFitting", "Cluster 2:", None, QtGui.QApplication.UnicodeUTF8))
        self.pushButtonMergeClusters.setText(QtGui.QApplication.translate("DialogCAlphaFlexibleFitting", "Merge Clusters", None, QtGui.QApplication.UnicodeUTF8))
        self.tabWidget.setTabText(self.tabWidget.indexOf(self.tabAlignments), QtGui.QApplication.translate("DialogCAlphaFlexibleFitting", "Alignments", None, QtGui.QApplication.UnicodeUTF8))
        self.radioButtonFlexibleFitting.setToolTip(QtGui.QApplication.translate("DialogCAlphaFlexibleFitting", "Align the backbone to the density while allowing for deformations", None, QtGui.QApplication.UnicodeUTF8))
        self.radioButtonFlexibleFitting.setText(QtGui.QApplication.translate("DialogCAlphaFlexibleFitting", "Flexible Alignment", None, QtGui.QApplication.UnicodeUTF8))
        self.radioButtonInterpolation.setText(QtGui.QApplication.translate("DialogCAlphaFlexibleFitting", "Interpolation", None, QtGui.QApplication.UnicodeUTF8))
        self.groupBoxFlexibleSettings.setTitle(QtGui.QApplication.translate("DialogCAlphaFlexibleFitting", "Flexible Fitting Settings:", None, QtGui.QApplication.UnicodeUTF8))
        self.doRigidInitializationLabel.setText(QtGui.QApplication.translate("DialogCAlphaFlexibleFitting", "Do Rigid Initialization", None, QtGui.QApplication.UnicodeUTF8))
        self.neighborhoodSizeLabel.setText(QtGui.QApplication.translate("DialogCAlphaFlexibleFitting", "Neighborhood Size", None, QtGui.QApplication.UnicodeUTF8))
        self.neighborhoodSizeSpinBox.setSuffix(QtGui.QApplication.translate("DialogCAlphaFlexibleFitting", " Neighbors", None, QtGui.QApplication.UnicodeUTF8))
        self.laplacianWeightLabel.setText(QtGui.QApplication.translate("DialogCAlphaFlexibleFitting", "Laplacian Weight", None, QtGui.QApplication.UnicodeUTF8))
        self.hardHandleWeightLabel.setText(QtGui.QApplication.translate("DialogCAlphaFlexibleFitting", "Hard Handle Weight", None, QtGui.QApplication.UnicodeUTF8))
        self.softHandleWeightLabel.setText(QtGui.QApplication.translate("DialogCAlphaFlexibleFitting", "Soft Handle Weight", None, QtGui.QApplication.UnicodeUTF8))
        self.useSoftHandlesLabel.setText(QtGui.QApplication.translate("DialogCAlphaFlexibleFitting", "Use Soft Handles", None, QtGui.QApplication.UnicodeUTF8))
        self.pushButtonRunFlexible.setText(QtGui.QApplication.translate("DialogCAlphaFlexibleFitting", "Ok", None, QtGui.QApplication.UnicodeUTF8))
        self.tabWidget.setTabText(self.tabWidget.indexOf(self.tabFlexibleFit), QtGui.QApplication.translate("DialogCAlphaFlexibleFitting", "Flexible Fit", None, QtGui.QApplication.UnicodeUTF8))

