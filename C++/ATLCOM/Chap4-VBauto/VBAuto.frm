VERSION 5.00
Begin VB.Form Form1 
   Caption         =   "Form1"
   ClientHeight    =   2670
   ClientLeft      =   60
   ClientTop       =   345
   ClientWidth     =   4680
   LinkTopic       =   "Form1"
   ScaleHeight     =   2670
   ScaleWidth      =   4680
   StartUpPosition =   3  'Windows ÇÃä˘íËíl
   Begin VB.CommandButton cmdSetVal 
      Caption         =   "SetVal"
      Height          =   615
      Left            =   2880
      TabIndex        =   4
      Top             =   1680
      Width           =   1095
   End
   Begin VB.CommandButton cmdGreeting 
      Caption         =   "Greeting"
      Height          =   615
      Left            =   480
      TabIndex        =   3
      Top             =   1680
      Width           =   1095
   End
   Begin VB.CommandButton cmdGetGender 
      Caption         =   "GetGender"
      Height          =   615
      Left            =   1680
      TabIndex        =   2
      Top             =   1680
      Width           =   1095
   End
   Begin VB.TextBox txtName 
      Height          =   375
      Left            =   360
      TabIndex        =   1
      Top             =   960
      Width           =   3735
   End
   Begin VB.Label lblRet 
      BorderStyle     =   1  'é¿ê¸
      Height          =   375
      Left            =   360
      TabIndex        =   0
      Top             =   360
      Width           =   3735
   End
End
Attribute VB_Name = "Form1"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False


Private Sub cmdGetGender_Click()
   Dim obj As New Auto
   Dim itf As IAuto2
   Set itf = obj
   lblRet = itf.GetGender(txtName)
   Set obj = Nothing
   Set itf = Nothing

End Sub

Private Sub cmdGreeting_Click()
   Dim obj As New Auto
   lblRet = obj.Greeting(txtName)
   Set obj = Nothing
End Sub

Private Sub cmdSetVal_Click()
   On Error GoTo except
   Dim obj As New Auto
   Dim itf As IAuto2
   Set itf = obj
   lblRet = ""
   obj.Value Val(txtName)
   itf.Value2 Val(txtName)
   Set obj = Nothing
   Set itf = Nothing
   Exit Sub
except:
   Dim str As String
   str = "Error from " + Err.Source + Chr$(10) + Chr$(13)
   str = str + Err.Description + Chr$(10) + Chr$(13)
   str = str + "HRESULT: " + Hex$(Err.Number)
   MsgBox str
End Sub
