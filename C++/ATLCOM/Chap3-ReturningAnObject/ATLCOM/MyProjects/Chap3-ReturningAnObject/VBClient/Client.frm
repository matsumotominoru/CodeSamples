VERSION 5.00
Begin VB.Form Form1 
   Caption         =   "Form1"
   ClientHeight    =   3195
   ClientLeft      =   60
   ClientTop       =   345
   ClientWidth     =   4680
   LinkTopic       =   "Form1"
   ScaleHeight     =   3195
   ScaleWidth      =   4680
   StartUpPosition =   3  'Windows Default
   Begin VB.CommandButton cmdTest 
      Caption         =   "Test"
      Height          =   495
      Left            =   1800
      TabIndex        =   0
      Top             =   1320
      Width           =   1215
   End
End
Attribute VB_Name = "Form1"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Private MainItf As RETURNINGANOBJECTLib.IMainObject
Private SepItf As RETURNINGANOBJECTLib.ISeparateObject
Private SepItf2 As RETURNINGANOBJECTLib.ISeparateObject


Private Sub cmdTest_Click()
    Set MainItf = New RETURNINGANOBJECTLib.MainObject
    MainItf.Display
    
    Set SepItf = MainItf.CreateSeparateObject
    SepItf.Display
    
    Set SepItf2 = MainItf.CreateAndInitializeSeparateObject
    SepItf2.Display

End Sub

