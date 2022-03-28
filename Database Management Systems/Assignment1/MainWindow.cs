using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Data.SqlClient;

namespace Assignment1
{
    public partial class MainWindow : Form
    {
        private SqlConnection connection;
        private SqlDataAdapter parentTableAdapter;
        private SqlDataAdapter childTableAdapter;
        private DataSet dataSet;


        public MainWindow()
        {
            InitializeComponent();
        }
    }
}
