VERSION 5.00
Begin VB.Form Main 
   Caption         =   "Test ColorObj"
   ClientHeight    =   4050
   ClientLeft      =   60
   ClientTop       =   345
   ClientWidth     =   4680
   LinkTopic       =   "Form1"
   ScaleHeight     =   4050
   ScaleWidth      =   4680
   StartUpPosition =   3  'Windows Default
   Begin VB.TextBox txtNewItem 
      Height          =   375
      Left            =   120
      TabIndex        =   4
      Top             =   720
      Width           =   4455
   End
   Begin VB.CommandButton cmdAddItem 
      Caption         =   "Add Item"
      Height          =   495
      Left            =   2760
      TabIndex        =   3
      Top             =   120
      Width           =   1215
   End
   Begin VB.ListBox lstColors 
      Height          =   2400
      Left            =   0
      TabIndex        =   1
      Top             =   1560
      Width           =   4695
   End
   Begin VB.CommandButton cmdShowObj 
      Caption         =   "Show Object"
      Height          =   495
      Left            =   480
      TabIndex        =   0
      Top             =   120
      Width           =   1215
   End
   Begin VB.Label lblMsg 
      BorderStyle     =   1  'Fixed Single
      Height          =   255
      Left            =   120
      TabIndex        =   2
      Top             =   1200
      Width           =   4455
   End
End
Attribute VB_Name = "Main"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit
Private itf As COLORSLib.IColorObject

Private Sub cmdAddItem_Click()
   If txtNewItem.Text = "" Then
      Exit Sub
   End If
   
   ' Read data into an array
   ReDim ColorArray(lstColors.ListCount) As String
   Dim x As Integer
   For x = 0 To lstColors.ListCount - 1
      ColorArray(x) = lstColors.List(x)
   Next
   ColorArray(lstColors.ListCount) = txtNewItem.Text
   itf.Colors = ColorArray
   cmdShowObj_Click
End Sub

Private Sub Form_Load()
    Set itf = New COLORSLib.ColorObject
End Sub

Private Sub cmdShowObj_Click()
   Dim Size As Long
   Dim ColorArray As Variant
   ColorArray = itf.Colors
   lstColors.Clear
   Size = UBound(ColorArray) - LBound(ColorArray) + 1
   lblMsg.Caption = "There are " & Str$(Size) _
      & " elements in " & TypeName(ColorArray)
   Dim x As Integer
   For x = LBound(ColorArray) To UBound(ColorArray)
      lstColors.AddItem ColorArray(x)
   Next
End Sub
