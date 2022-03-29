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
            connection = new SqlConnection(@"Data Source = DESKTOP-PJI8ALC;Initial Catalog=FCSB; Integrated Security = True");
            dataSet = new DataSet();
            childDataAdapter = new SqlDataAdapter("SELECT* FROM Trophies", connection);
            parentDataAdapter = new SqlDataAdapter("SELECT* FROM TeamFormations", connection);
            
            childCommandBuilder = new SqlCommandBuilder(childDataAdapter);

            parentDataAdapter.Fill(dataSet, "TeamFormations");
            childDataAdapter.Fill(dataSet, "Trophies");
            
            DataRelation dataRelation = new DataRelation("FK_TeamFormations_Trophies",
            dataSet.Tables["TeamFormations"].Columns["formation"], dataSet.Tables["Trophies"].Columns["mostPlayedFormation"]);
            dataSet.Relations.Add(dataRelation);

            bsParent = new BindingSource();
            bsChild = new BindingSource();
            bsParent.DataSource = dataSet;
            bsParent.DataMember = "TeamFormations";
            bsChild.DataSource = bsParent;
            bsChild.DataMember = "FK_TeamFormations_Trophies";

            childDataGridView.AutoSizeColumnsMode = DataGridViewAutoSizeColumnsMode.Fill;
            parentDataGridView.AutoSizeColumnsMode = DataGridViewAutoSizeColumnsMode.Fill;
            parentDataGridView.DataSource = bsParent;
            childDataGridView.DataSource = bsChild;

            String[] childColumnNames = { "Trophy ID", "Type", "Date", "Formation" };
            for (int i = 0; i < 4; ++i)
                childDataGridView.Columns[i].HeaderCell.Value = childColumnNames[i];

            String[] parentColumnNames = { "Formation", "Formation Style" };
            for (int i = 0; i < 2; ++i)
                parentDataGridView.Columns[i].HeaderCell.Value = parentColumnNames[i];
        }

        private void updateDatabaseBtn_Click(object sender, EventArgs e)
        {
            // TODO
            if (connection == null)
                return;

            try
            {
                childDataAdapter.Update(dataSet, "Trophies");
            }
            catch (System.InvalidOperationException exception)
            {
                MessageBox.Show(exception.Message);
            }
            catch (System.Data.InvalidConstraintException exception)
            {
                MessageBox.Show(exception.Message);
            }
            catch (System.Exception exception)
            {
                MessageBox.Show(exception.Message);
            }
        }

        private void addBtn_Click(object sender, EventArgs e)
        {
            // TODO
            if (connection == null)
                return;

            childDataAdapter.InsertCommand = new SqlCommand(
                "INSERT INTO Trophies (trophyType, winningDate, mostPlayedFormation) " +
                "VALUES (@type, @date, @formation);", connection);
            childDataAdapter.InsertCommand.Parameters.Add("@type", SqlDbType.VarChar).Value = trophyTextBox.Text;
            childDataAdapter.InsertCommand.Parameters.Add("@date", SqlDbType.VarChar).Value = dateTextBox.Text;
            childDataAdapter.InsertCommand.Parameters.Add("@formation", SqlDbType.VarChar).Value = formationTextBox.Text;

            connection.Open();
            try
            {
                childDataAdapter.InsertCommand.ExecuteNonQuery();
            }
            catch (System.Exception exception)
            {
                MessageBox.Show(exception.Message);
            }
            finally
            {
                connection.Close();
            }
        }

        private void updateBtn_Click(object sender, EventArgs e)
        {
            // TODO
            if (connection == null)
                return;

            childDataAdapter.InsertCommand = new SqlCommand("UPDATE Trophies " +
                "SET trophyType = @type, winningDate = @date, mostPlayedFormation = @formation " +
                "WHERE trophyID = @id;", connection);

            childDataAdapter.InsertCommand.Parameters.Add("@type", SqlDbType.VarChar).Value = trophyTextBox.Text;
            childDataAdapter.InsertCommand.Parameters.Add("@date", SqlDbType.VarChar).Value = dateTextBox.Text;
            childDataAdapter.InsertCommand.Parameters.Add("@formation", SqlDbType.VarChar).Value = formationTextBox.Text;

            try
            {
                childDataAdapter.InsertCommand.Parameters.Add("@id", SqlDbType.VarChar).Value = Int32.Parse(idTextBox.Text);
            }
            catch (System.Exception exception)
            {
                MessageBox.Show(exception.Message);
            }

            connection.Open();
            try
            {
                childDataAdapter.InsertCommand.ExecuteNonQuery();
            }
            catch (System.Exception exception)
            {
                MessageBox.Show(exception.Message);
            }
            finally
            {
                connection.Close();
            }
        }

        private void deleteBtn_Click(object sender, EventArgs e)
        {
            // TODO
            if (connection == null)
                return;

            childDataAdapter.InsertCommand = new SqlCommand("DELETE FROM Trophies " +
                "WHERE trophyID = @id;", connection);

            try
            {
                childDataAdapter.InsertCommand.Parameters.Add("@id", SqlDbType.VarChar).Value = Int32.Parse(idTextBox.Text);
            }
            catch (System.Exception exception)
            {
                MessageBox.Show(exception.Message);
            }

            connection.Open();
            try
            {
                childDataAdapter.InsertCommand.ExecuteNonQuery();
            }
            catch (System.Exception exception)
            {
                MessageBox.Show(exception.Message);
            }
            finally
            {
                connection.Close();
            }
        }
    }
}
