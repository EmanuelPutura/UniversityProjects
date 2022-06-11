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
            connection = new SqlConnection(@"Data Source = DESKTOP-PJI8ALC;Initial Catalog=PracticalExamII; Integrated Security = True");
            dataSet = new DataSet();
            childDataAdapter = new SqlDataAdapter("SELECT* FROM Clubs", connection);
            parentDataAdapter = new SqlDataAdapter("SELECT* FROM Locations", connection);
            
            childCommandBuilder = new SqlCommandBuilder(childDataAdapter);

            parentDataAdapter.Fill(dataSet, "Locations");
            childDataAdapter.Fill(dataSet, "Clubs");
            
            DataRelation dataRelation = new DataRelation("FK_Locations_Clubs",
                    dataSet.Tables["Locations"].Columns["id"], dataSet.Tables["Clubs"].Columns["lid"]);
            dataSet.Relations.Add(dataRelation);

            bsParent = new BindingSource();
            bsChild = new BindingSource();
            bsParent.DataSource = dataSet;
            bsParent.DataMember = "Locations";
            bsChild.DataSource = bsParent;
            bsChild.DataMember = "FK_Locations_Clubs";

            dvgClubs.AutoSizeColumnsMode = DataGridViewAutoSizeColumnsMode.Fill;
            dvgLocations.AutoSizeColumnsMode = DataGridViewAutoSizeColumnsMode.Fill;
            dvgLocations.DataSource = bsParent;
            dvgClubs.DataSource = bsChild;

            String[] childColumnNames = { "Club ID", "Name", "Opening Year", "Starts Number", "Location ID" };
            for (int i = 0; i < 4; ++i)
                dvgClubs.Columns[i].HeaderCell.Value = childColumnNames[i];

            String[] parentColumnNames = { "Location ID", "Name", "County", "Country" };
            for (int i = 0; i < 2; ++i)
                dvgLocations.Columns[i].HeaderCell.Value = parentColumnNames[i];
        }

        private void updateDatabaseBtn_Click(object sender, EventArgs e)
        {
            // TODO
            if (connection == null)
                return;

            try
            {
                childDataAdapter.Update(dataSet, "Clubs");
            }
            catch (System.Exception exception)
            {
                MessageBox.Show(exception.Message);
            }
        }

        private void label6_Click(object sender, EventArgs e)
        {

        }
    }
}
