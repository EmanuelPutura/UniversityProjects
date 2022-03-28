﻿using System;
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
        private SqlCommandBuilder commandBuilder;
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
            parentTableAdapter = new SqlDataAdapter("SELECT* FROM TeamFormations", connection);
            childTableAdapter = new SqlDataAdapter("SELECT* FROM Trophies", connection);
            commandBuilder = new SqlCommandBuilder(parentTableAdapter);

            parentTableAdapter.Fill(dataSet, "TeamFormations");
            childTableAdapter.Fill(dataSet, "Trophies");
            
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
            childDataGridView.DataSource = bsChild;
            parentDataGridView.DataSource = bsParent;

            String[] childColumnNames = { "Trophy ID", "Type", "Date", "Formation" };
            for (int i = 0; i < 4; ++i)
                childDataGridView.Columns[i].HeaderCell.Value = childColumnNames[i];

            String[] parentColumnNames = { "Formation", "Formation Style" };
            for (int i = 0; i < 2; ++i)
                parentDataGridView.Columns[i].HeaderCell.Value = parentColumnNames[i];
        }
    }
}
