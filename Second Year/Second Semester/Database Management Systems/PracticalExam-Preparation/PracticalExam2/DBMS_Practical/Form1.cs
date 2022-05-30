using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Data.SqlClient;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Exam_Try_Good
{
    public partial class Form1 : Form
    {
        SqlConnection connection;
        SqlDataAdapter dataAdapterParent, dataAdapterChild;
        DataSet dataSet;
        SqlCommandBuilder commandBuilderParent, commandBuilderChild;
        BindingSource bindingSourceParent, bindingSourceChild;
        // the connection string we need: name of the machine + name of the database + true for authentification
        string connectionString = @"Data Source=DESKTOP-M2EDLJ1;" +
                @"Initial Catalog=Exam2;" +
                @"Integrated Security=true";
        public Form1()
        {
            InitializeComponent();
        }

        private void button_display_Click(object sender, EventArgs e)
        {
            try
            {
                // we create the connection to the data base
                connection = new SqlConnection(connectionString);

                // complete set of data that includes tables, constraints, and relationships among the tables
                dataSet = new DataSet();

                // interaction with existing data sources is controlled through the DataAdapter
                dataAdapterParent = new SqlDataAdapter("SELECT * FROM Projects", connection);
                dataAdapterChild = new SqlDataAdapter("SELECT * FROM Tasks", connection);

                // helps generate update, delete and insert commands on a single database table for a data adapter
                commandBuilderParent = new SqlCommandBuilder(dataAdapterParent);
                commandBuilderChild = new SqlCommandBuilder(dataAdapterChild);

                // the Fill method of the DataAdapter is used to populate a DataSet with the results of the SelectCommand of the DataAdapter
                dataAdapterParent.Fill(dataSet, "Projects");
                dataAdapterChild.Fill(dataSet, "Tasks");

                // a DataRelation is used to relate two DataTable objects to each other through DataColumn objects
                DataRelation dataRelation = new DataRelation("FK_Projects_Tasks",
                    dataSet.Tables["Projects"].Columns["id_project"],
                    dataSet.Tables["Tasks"].Columns["id_project"]);

                // adds a single DataRelation to the Relations collection of the DataSet. 
                dataSet.Relations.Add(dataRelation);

                // creating a binding source for both tables
                bindingSourceParent = new BindingSource();
                bindingSourceChild = new BindingSource();

                // adding the data member from the Projects table
                bindingSourceParent.DataSource = dataSet;
                bindingSourceParent.DataMember = "Projects";

                // adding the data member for the Tasks through the relationship with Projects (1:n, FK)
                bindingSourceChild.DataSource = bindingSourceParent;
                bindingSourceChild.DataMember = "FK_Projects_Tasks";

                // setting the newly created binding sources to the data grid views
                dgvProjects.DataSource = bindingSourceParent;
                dgvTasks.DataSource = bindingSourceChild;
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message);
            }
        }

        private void button_update_Click(object sender, EventArgs e)
        {
            try
            {
                // update the data set (args: dataSet + name of table)
                dataAdapterParent.Update(dataSet, "Projects");
                dataAdapterChild.Update(dataSet, "Tasks");
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message);
            }
        }
    }
}
