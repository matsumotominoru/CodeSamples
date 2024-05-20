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
   StartUpPosition =   3  'Windows ‚ÌŠù’è’l
   Begin VB.CommandButton cmdCalculate 
      Caption         =   "Caluculate"
      Height          =   495
      Left            =   3120
      TabIndex        =   2
      Top             =   2160
      Width           =   1455
   End
   Begin VB.CommandButton cmdHide 
      Caption         =   "Hide"
      Height          =   495
      Left            =   3120
      TabIndex        =   1
      Top             =   1320
      Width           =   1455
   End
   Begin VB.CommandButton cmdShow 
      Caption         =   "Show"
      Height          =   495
      Left            =   3120
      TabIndex        =   0
      Top             =   480
      Width           =   1455
   End
End
Attribute VB_Name = "Form1"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Private itf As COMDIALOGPROJECTLib.IComDialog
Private itfCalcEaster As ICalcEaster


Private Sub cmdCalculate_Click()
On Error GoTo err_Generic
  
    itfCalcEaster.Year = 1984
    itfCalcEaster.CalculateEaster

    MsgBox "Easter was " & itfCalcEaster.Day & "/" & itfCalcEaster.Month & " in " & itfCalcEaster.Year
    Exit Sub
    
err_Generic:
    MsgBox "Error: " & Err.Number & vbCrLf & Err.Description
End Sub

Private Sub cmdHide_Click()
    itf.Visible = False
End Sub

Private Sub cmdShow_Click()
    itf.Visible = True
End Sub

Private Sub Form_Load()
    Set itf = New COMDIALOGPROJECTLib.ComDialog
    Set itfCalcEaster = itf
End Sub
