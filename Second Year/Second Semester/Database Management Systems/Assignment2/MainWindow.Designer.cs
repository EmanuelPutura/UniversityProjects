
namespace Assignment2
{
    partial class MainWindow
    {
        /// <summary>
        ///  Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        ///  Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        ///  Required method for Designer support - do not modify
        ///  the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.tableLayoutPanel1 = new System.Windows.Forms.TableLayoutPanel();
            this.childDataGridView = new System.Windows.Forms.DataGridView();
            this.parentDataGridView = new System.Windows.Forms.DataGridView();
            this.tableLayoutPanel3 = new System.Windows.Forms.TableLayoutPanel();
            this.updateDatabaseBtn = new System.Windows.Forms.Button();
            this.connectBtn = new System.Windows.Forms.Button();
            this.label5 = new System.Windows.Forms.Label();
            this.label6 = new System.Windows.Forms.Label();
            this.tableLayoutPanel1.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.childDataGridView)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.parentDataGridView)).BeginInit();
            this.tableLayoutPanel3.SuspendLayout();
            this.SuspendLayout();
            // 
            // tableLayoutPanel1
            // 
            this.tableLayoutPanel1.ColumnCount = 2;
            this.tableLayoutPanel1.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 50F));
            this.tableLayoutPanel1.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 50F));
            this.tableLayoutPanel1.Controls.Add(this.childDataGridView, 0, 1);
            this.tableLayoutPanel1.Controls.Add(this.parentDataGridView, 1, 1);
            this.tableLayoutPanel1.Controls.Add(this.tableLayoutPanel3, 0, 2);
            this.tableLayoutPanel1.Controls.Add(this.label5, 0, 0);
            this.tableLayoutPanel1.Controls.Add(this.label6, 1, 0);
            this.tableLayoutPanel1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.tableLayoutPanel1.GrowStyle = System.Windows.Forms.TableLayoutPanelGrowStyle.AddColumns;
            this.tableLayoutPanel1.Location = new System.Drawing.Point(0, 0);
            this.tableLayoutPanel1.Name = "tableLayoutPanel1";
            this.tableLayoutPanel1.RowCount = 3;
            this.tableLayoutPanel1.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 5F));
            this.tableLayoutPanel1.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 65F));
            this.tableLayoutPanel1.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 30F));
            this.tableLayoutPanel1.Size = new System.Drawing.Size(966, 433);
            this.tableLayoutPanel1.TabIndex = 0;
            // 
            // childDataGridView
            // 
            this.childDataGridView.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.childDataGridView.Dock = System.Windows.Forms.DockStyle.Fill;
            this.childDataGridView.Location = new System.Drawing.Point(10, 31);
            this.childDataGridView.Margin = new System.Windows.Forms.Padding(10);
            this.childDataGridView.Name = "childDataGridView";
            this.childDataGridView.RowHeadersWidth = 51;
            this.childDataGridView.RowTemplate.Height = 29;
            this.childDataGridView.Size = new System.Drawing.Size(463, 261);
            this.childDataGridView.TabIndex = 0;
            // 
            // parentDataGridView
            // 
            this.parentDataGridView.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.parentDataGridView.Dock = System.Windows.Forms.DockStyle.Fill;
            this.parentDataGridView.Location = new System.Drawing.Point(493, 31);
            this.parentDataGridView.Margin = new System.Windows.Forms.Padding(10);
            this.parentDataGridView.Name = "parentDataGridView";
            this.parentDataGridView.RowHeadersWidth = 51;
            this.parentDataGridView.RowTemplate.Height = 29;
            this.parentDataGridView.Size = new System.Drawing.Size(463, 261);
            this.parentDataGridView.TabIndex = 1;
            // 
            // tableLayoutPanel3
            // 
            this.tableLayoutPanel3.ColumnCount = 1;
            this.tableLayoutPanel1.SetColumnSpan(this.tableLayoutPanel3, 2);
            this.tableLayoutPanel3.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 100F));
            this.tableLayoutPanel3.Controls.Add(this.updateDatabaseBtn, 0, 1);
            this.tableLayoutPanel3.Controls.Add(this.connectBtn, 0, 0);
            this.tableLayoutPanel3.Dock = System.Windows.Forms.DockStyle.Fill;
            this.tableLayoutPanel3.Location = new System.Drawing.Point(3, 305);
            this.tableLayoutPanel3.Name = "tableLayoutPanel3";
            this.tableLayoutPanel3.RowCount = 2;
            this.tableLayoutPanel3.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 50F));
            this.tableLayoutPanel3.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 50F));
            this.tableLayoutPanel3.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Absolute, 20F));
            this.tableLayoutPanel3.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Absolute, 20F));
            this.tableLayoutPanel3.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Absolute, 20F));
            this.tableLayoutPanel3.Size = new System.Drawing.Size(960, 125);
            this.tableLayoutPanel3.TabIndex = 3;
            // 
            // updateDatabaseBtn
            // 
            this.updateDatabaseBtn.Dock = System.Windows.Forms.DockStyle.Fill;
            this.updateDatabaseBtn.Location = new System.Drawing.Point(5, 67);
            this.updateDatabaseBtn.Margin = new System.Windows.Forms.Padding(5);
            this.updateDatabaseBtn.Name = "updateDatabaseBtn";
            this.updateDatabaseBtn.Size = new System.Drawing.Size(950, 53);
            this.updateDatabaseBtn.TabIndex = 1;
            this.updateDatabaseBtn.Text = "Update Database";
            this.updateDatabaseBtn.UseVisualStyleBackColor = true;
            this.updateDatabaseBtn.Click += new System.EventHandler(this.updateDatabaseBtn_Click);
            // 
            // connectBtn
            // 
            this.connectBtn.Dock = System.Windows.Forms.DockStyle.Fill;
            this.connectBtn.Location = new System.Drawing.Point(5, 5);
            this.connectBtn.Margin = new System.Windows.Forms.Padding(5);
            this.connectBtn.Name = "connectBtn";
            this.connectBtn.Size = new System.Drawing.Size(950, 52);
            this.connectBtn.TabIndex = 0;
            this.connectBtn.Text = "Connect/Refresh Database";
            this.connectBtn.UseVisualStyleBackColor = true;
            this.connectBtn.Click += new System.EventHandler(this.connectBtn_Click);
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Dock = System.Windows.Forms.DockStyle.Fill;
            this.label5.Location = new System.Drawing.Point(3, 3);
            this.label5.Margin = new System.Windows.Forms.Padding(3, 3, 3, 0);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(477, 18);
            this.label5.TabIndex = 4;
            this.label5.Text = "Trophies Table (Child)";
            this.label5.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.Dock = System.Windows.Forms.DockStyle.Fill;
            this.label6.Location = new System.Drawing.Point(486, 3);
            this.label6.Margin = new System.Windows.Forms.Padding(3, 3, 3, 0);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(477, 18);
            this.label6.TabIndex = 5;
            this.label6.Text = "TeamFormations Table (Parent)";
            this.label6.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // MainWindow
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 20F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(966, 433);
            this.Controls.Add(this.tableLayoutPanel1);
            this.Name = "MainWindow";
            this.Text = "Assignment 1";
            this.tableLayoutPanel1.ResumeLayout(false);
            this.tableLayoutPanel1.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.childDataGridView)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.parentDataGridView)).EndInit();
            this.tableLayoutPanel3.ResumeLayout(false);
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.TableLayoutPanel tableLayoutPanel1;
        private System.Windows.Forms.DataGridView childDataGridView;
        private System.Windows.Forms.DataGridView parentDataGridView;
        private System.Windows.Forms.TableLayoutPanel tableLayoutPanel3;
        private System.Windows.Forms.Button updateDatabaseBtn;
        private System.Windows.Forms.Button connectBtn;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.Label label6;
    }
}

