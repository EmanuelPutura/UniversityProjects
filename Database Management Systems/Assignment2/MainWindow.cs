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
using System.Configuration;

namespace Assignment2
{
    public partial class MainWindow : Form
    {
        private SqlConnection connection;
        private SqlDataAdapter parentDataAdapter;
        private SqlDataAdapter childDataAdapter;
        private DataSet dataSet;
        private SqlCommandBuilder childCommandBuilder;
        private BindingSource bsParent;
        private BindingSource bsChild;

        public MainWindow()
        {
            InitializeComponent();
        }

        private void connectBtn_Click(object sender, EventArgs e)
        {
            // App.config data
            var connectionString = ConfigurationManager.ConnectionStrings["connectionString"].ConnectionString;
            var parentTableName = ConfigurationManager.AppSettings["parentTable"];
            var childTableName = ConfigurationManager.AppSettings["childTable"];
            var parentPrimaryKey = ConfigurationManager.AppSettings["parentPK"];
            var childForeignKey = ConfigurationManager.AppSettings["childFK"];

            connection = new SqlConnection(connectionString);
            dataSet = new DataSet();

            childDataAdapter = new SqlDataAdapter($"SELECT* FROM {childTableName}", connection);
            parentDataAdapter = new SqlDataAdapter($"SELECT* FROM {parentTableName}", connection);
            
            childCommandBuilder = new SqlCommandBuilder(childDataAdapter);

            dataSet.Clear();
            parentDataAdapter.Fill(dataSet, parentTableName);
            childDataAdapter.Fill(dataSet, childTableName);
            
            DataRelation dataRelation = new DataRelation($"FK_{parentTableName}_{childTableName}",
                    dataSet.Tables[parentTableName].Columns[parentPrimaryKey], dataSet.Tables[childTableName].Columns[childForeignKey]);
            dataSet.Relations.Add(dataRelation);

            bsParent = new BindingSource();
            bsChild = new BindingSource();
            bsParent.DataSource = dataSet;
            bsParent.DataMember = parentTableName;
            bsChild.DataSource = bsParent;
            bsChild.DataMember = $"FK_{parentTableName}_{childTableName}";

            childDataGridView.AutoSizeColumnsMode = DataGridViewAutoSizeColumnsMode.Fill;
            parentDataGridView.AutoSizeColumnsMode = DataGridViewAutoSizeColumnsMode.Fill;

            parentDataGridView.DataSource = bsParent;
            childDataGridView.DataSource = bsChild;
        }

        private void updateDatabaseBtn_Click(object sender, EventArgs e)
        {
            // TODO
            if (connection == null)
                return;

            try
            {
                var childTableName = ConfigurationManager.AppSettings["childTable"];
                childDataAdapter.Update(dataSet, childTableName);
            }
            catch (System.Exception exception)
            {
                MessageBox.Show(exception.Message);
            }
        }
    }
}
