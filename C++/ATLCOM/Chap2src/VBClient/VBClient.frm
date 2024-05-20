VERSION 5.00
Begin VB.Form Form1 
   Caption         =   "Form1"
   ClientHeight    =   615
   ClientLeft      =   60
   ClientTop       =   345
   ClientWidth     =   4635
   LinkTopic       =   "Form1"
   ScaleHeight     =   615
   ScaleWidth      =   4635
   StartUpPosition =   3  'Windows ‚ÌŠù’è’l
   Begin VB.TextBox txtYear 
      Height          =   350
      Left            =   1080
      TabIndex        =   1
      Top             =   105
      Width           =   1455
   End
   Begin VB.CommandButton cmdCalculate 
      Caption         =   "Calculate"
      Height          =   375
      Left            =   2760
      TabIndex        =   0
      Top             =   120
      Width           =   1695
   End
   Begin VB.Label Label1 
      AutoSize        =   -1  'True
      Caption         =   "Enter year:"
      Height          =   195
      Left            =   120
      TabIndex        =   2
      Top             =   240
      Width           =   765
   End
End
Attribute VB_Name = "Form1"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Private Sub cmdCalculate_Click()
On Error GoTo err_Generic
    Dim itf As SIMPLELib.ICalcEaster
    Set itf = New SIMPLELib.CalcEaster
    
    itf.Year = CInt(txtYear)
    itf.CalculateEaster

    MsgBox "Easter: " & itf.Day & "/" & itf.Month & " in " & itf.Year
    Exit Sub
    
err_Generic:
    MsgBox "Error: " & Err.Number & vbCrLf & Err.Description
End Sub

