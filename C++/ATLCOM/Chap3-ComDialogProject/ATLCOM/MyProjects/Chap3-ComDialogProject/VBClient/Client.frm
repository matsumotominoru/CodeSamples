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
   Begin VB.CommandButton cmdHide 
      Caption         =   "Hide"
      Height          =   495
      Left            =   3120
      TabIndex        =   1
      Top             =   1560
      Width           =   1455
   End
   Begin VB.CommandButton cmdShow 
      Caption         =   "Show"
      Height          =   495
      Left            =   3120
      TabIndex        =   0
      Top             =   720
      Width           =   1455
   End
End
Attribute VB_Name = "Form1"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Private itf As COMDIALOGPROJECTLib.IComDialog

Private Sub cmdHide_Click()
    itf.Visible = False
End Sub

Private Sub cmdShow_Click()
    itf.Visible = True
End Sub

Private Sub Form_Load()
    Set itf = New COMDIALOGPROJECTLib.ComDialog
End Sub
