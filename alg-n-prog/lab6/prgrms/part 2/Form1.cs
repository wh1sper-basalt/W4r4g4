using System;
using System.Drawing;
using System.Windows.Forms;

namespace Variant2_WinForms
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            linkLabel1.Text = "Привет, это Я!";
            button1.Text = "Уже нажали";
            button1.Enabled = false;
            button1.BackColor = Color.LightGreen;
        }

        private void linkLabel1_LinkClicked(object sender, LinkLabelLinkClickedEventArgs e)
        {
            MessageBox.Show("Клик по ссылке!", "Информация");
            linkLabel1.LinkVisited = true;
        }
    }
}