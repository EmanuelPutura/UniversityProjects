﻿
namespace Assignment1
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
            this.opsGroupBox = new System.Windows.Forms.GroupBox();
            this.tableLayoutPanel2 = new System.Windows.Forms.TableLayoutPanel();
            this.formationTextBox = new System.Windows.Forms.TextBox();
            this.dateTextBox = new System.Windows.Forms.TextBox();
            this.label1 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.trophyTextBox = new System.Windows.Forms.TextBox();
            this.tableLayoutPanel3 = new System.Windows.Forms.TableLayoutPanel();
            this.connectBtn = new System.Windows.Forms.Button();
            this.updateDatabaseBtn = new System.Windows.Forms.Button();
            this.opsBtn = new System.Windows.Forms.Button();
            this.tableLayoutPanel1.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.childDataGridView)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.parentDataGridView)).BeginInit();
            this.opsGroupBox.SuspendLayout();
            this.tableLayoutPanel2.SuspendLayout();
            this.tableLayoutPanel3.SuspendLayout();
            this.SuspendLayout();
            // 
            // tableLayoutPanel1
            // 
            this.tableLayoutPanel1.ColumnCount = 2;
            this.tableLayoutPanel1.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 50F));
            this.tableLayoutPanel1.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 50F));
            this.tableLayoutPanel1.Controls.Add(this.childDataGridView, 0, 0);
            this.tableLayoutPanel1.Controls.Add(this.parentDataGridView, 1, 0);
            this.tableLayoutPanel1.Controls.Add(this.opsGroupBox, 0, 1);
            this.tableLayoutPanel1.Controls.Add(this.tableLayoutPanel3, 1, 1);
            this.tableLayoutPanel1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.tableLayoutPanel1.GrowStyle = System.Windows.Forms.TableLayoutPanelGrowStyle.AddColumns;
            this.tableLayoutPanel1.Location = new System.Drawing.Point(0, 0);
            this.tableLayoutPanel1.Name = "tableLayoutPanel1";
            this.tableLayoutPanel1.RowCount = 2;
            this.tableLayoutPanel1.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 60F));
            this.tableLayoutPanel1.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 40F));
            this.tableLayoutPanel1.Size = new System.Drawing.Size(800, 450);
            this.tableLayoutPanel1.TabIndex = 0;
            // 
            // childDataGridView
            // 
            this.childDataGridView.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.childDataGridView.Dock = System.Windows.Forms.DockStyle.Fill;
            this.childDataGridView.Location = new System.Drawing.Point(10, 10);
            this.childDataGridView.Margin = new System.Windows.Forms.Padding(10);
            this.childDataGridView.Name = "childDataGridView";
            this.childDataGridView.RowHeadersWidth = 51;
            this.childDataGridView.RowTemplate.Height = 29;
            this.childDataGridView.Size = new System.Drawing.Size(380, 250);
            this.childDataGridView.TabIndex = 0;
            // 
            // parentDataGridView
            // 
            this.parentDataGridView.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.parentDataGridView.Dock = System.Windows.Forms.DockStyle.Fill;
            this.parentDataGridView.Location = new System.Drawing.Point(410, 10);
            this.parentDataGridView.Margin = new System.Windows.Forms.Padding(10);
            this.parentDataGridView.Name = "parentDataGridView";
            this.parentDataGridView.RowHeadersWidth = 51;
            this.parentDataGridView.RowTemplate.Height = 29;
            this.parentDataGridView.Size = new System.Drawing.Size(380, 250);
            this.parentDataGridView.TabIndex = 1;
            // 
            // opsGroupBox
            // 
            this.opsGroupBox.Controls.Add(this.tableLayoutPanel2);
            this.opsGroupBox.Dock = System.Windows.Forms.DockStyle.Fill;
            this.opsGroupBox.Location = new System.Drawing.Point(3, 273);
            this.opsGroupBox.Name = "opsGroupBox";
            this.opsGroupBox.Size = new System.Drawing.Size(394, 174);
            this.opsGroupBox.TabIndex = 2;
            this.opsGroupBox.TabStop = false;
            this.opsGroupBox.Text = "Add/Delete/Update";
            // 
            // tableLayoutPanel2
            // 
            this.tableLayoutPanel2.ColumnCount = 2;
            this.tableLayoutPanel2.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 40F));
            this.tableLayoutPanel2.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 60F));
            this.tableLayoutPanel2.Controls.Add(this.formationTextBox, 1, 2);
            this.tableLayoutPanel2.Controls.Add(this.dateTextBox, 1, 1);
            this.tableLayoutPanel2.Controls.Add(this.label1, 0, 0);
            this.tableLayoutPanel2.Controls.Add(this.label2, 0, 1);
            this.tableLayoutPanel2.Controls.Add(this.label3, 0, 2);
            this.tableLayoutPanel2.Controls.Add(this.trophyTextBox, 1, 0);
            this.tableLayoutPanel2.Dock = System.Windows.Forms.DockStyle.Fill;
            this.tableLayoutPanel2.Location = new System.Drawing.Point(3, 23);
            this.tableLayoutPanel2.Name = "tableLayoutPanel2";
            this.tableLayoutPanel2.RowCount = 3;
            this.tableLayoutPanel2.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 33.33333F));
            this.tableLayoutPanel2.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 33.33333F));
            this.tableLayoutPanel2.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 33.33333F));
            this.tableLayoutPanel2.Size = new System.Drawing.Size(388, 148);
            this.tableLayoutPanel2.TabIndex = 0;
            // 
            // formationTextBox
            // 
            this.formationTextBox.Dock = System.Windows.Forms.DockStyle.Fill;
            this.formationTextBox.Location = new System.Drawing.Point(158, 101);
            this.formationTextBox.Multiline = true;
            this.formationTextBox.Name = "formationTextBox";
            this.formationTextBox.Size = new System.Drawing.Size(227, 44);
            this.formationTextBox.TabIndex = 5;
            // 
            // dateTextBox
            // 
            this.dateTextBox.Dock = System.Windows.Forms.DockStyle.Fill;
            this.dateTextBox.Location = new System.Drawing.Point(158, 52);
            this.dateTextBox.Multiline = true;
            this.dateTextBox.Name = "dateTextBox";
            this.dateTextBox.Size = new System.Drawing.Size(227, 43);
            this.dateTextBox.TabIndex = 4;
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.label1.Location = new System.Drawing.Point(3, 0);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(149, 49);
            this.label1.TabIndex = 0;
            this.label1.Text = "Trophy:";
            this.label1.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Dock = System.Windows.Forms.DockStyle.Fill;
            this.label2.Location = new System.Drawing.Point(3, 49);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(149, 49);
            this.label2.TabIndex = 1;
            this.label2.Text = "Date:";
            this.label2.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Dock = System.Windows.Forms.DockStyle.Fill;
            this.label3.Location = new System.Drawing.Point(3, 98);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(149, 50);
            this.label3.TabIndex = 2;
            this.label3.Text = "Preferred Formation:";
            this.label3.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // trophyTextBox
            // 
            this.trophyTextBox.Dock = System.Windows.Forms.DockStyle.Fill;
            this.trophyTextBox.Location = new System.Drawing.Point(158, 3);
            this.trophyTextBox.Multiline = true;
            this.trophyTextBox.Name = "trophyTextBox";
            this.trophyTextBox.Size = new System.Drawing.Size(227, 43);
            this.trophyTextBox.TabIndex = 6;
            // 
            // tableLayoutPanel3
            // 
            this.tableLayoutPanel3.ColumnCount = 1;
            this.tableLayoutPanel3.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 100F));
            this.tableLayoutPanel3.Controls.Add(this.opsBtn, 0, 2);
            this.tableLayoutPanel3.Controls.Add(this.updateDatabaseBtn, 0, 1);
            this.tableLayoutPanel3.Controls.Add(this.connectBtn, 0, 0);
            this.tableLayoutPanel3.Dock = System.Windows.Forms.DockStyle.Fill;
            this.tableLayoutPanel3.Location = new System.Drawing.Point(403, 273);
            this.tableLayoutPanel3.Name = "tableLayoutPanel3";
            this.tableLayoutPanel3.RowCount = 3;
            this.tableLayoutPanel3.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 33.33333F));
            this.tableLayoutPanel3.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 33.33333F));
            this.tableLayoutPanel3.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 33.33333F));
            this.tableLayoutPanel3.Size = new System.Drawing.Size(394, 174);
            this.tableLayoutPanel3.TabIndex = 3;
            // 
            // connectBtn
            // 
            this.connectBtn.Dock = System.Windows.Forms.DockStyle.Fill;
            this.connectBtn.Location = new System.Drawing.Point(10, 10);
            this.connectBtn.Margin = new System.Windows.Forms.Padding(10);
            this.connectBtn.Name = "connectBtn";
            this.connectBtn.Size = new System.Drawing.Size(374, 38);
            this.connectBtn.TabIndex = 0;
            this.connectBtn.Text = "Connect";
            this.connectBtn.UseVisualStyleBackColor = true;
            // 
            // updateDatabaseBtn
            // 
            this.updateDatabaseBtn.Dock = System.Windows.Forms.DockStyle.Fill;
            this.updateDatabaseBtn.Location = new System.Drawing.Point(10, 68);
            this.updateDatabaseBtn.Margin = new System.Windows.Forms.Padding(10);
            this.updateDatabaseBtn.Name = "updateDatabaseBtn";
            this.updateDatabaseBtn.Size = new System.Drawing.Size(374, 38);
            this.updateDatabaseBtn.TabIndex = 1;
            this.updateDatabaseBtn.Text = "Update Database";
            this.updateDatabaseBtn.UseVisualStyleBackColor = true;
            // 
            // opsBtn
            // 
            this.opsBtn.Dock = System.Windows.Forms.DockStyle.Fill;
            this.opsBtn.Location = new System.Drawing.Point(10, 126);
            this.opsBtn.Margin = new System.Windows.Forms.Padding(10);
            this.opsBtn.Name = "opsBtn";
            this.opsBtn.Size = new System.Drawing.Size(374, 38);
            this.opsBtn.TabIndex = 2;
            this.opsBtn.Text = "Perform Operation";
            this.opsBtn.UseVisualStyleBackColor = true;
            // 
            // MainWindow
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 20F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(800, 450);
            this.Controls.Add(this.tableLayoutPanel1);
            this.Name = "MainWindow";
            this.Text = "Form1";
            this.tableLayoutPanel1.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.childDataGridView)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.parentDataGridView)).EndInit();
            this.opsGroupBox.ResumeLayout(false);
            this.tableLayoutPanel2.ResumeLayout(false);
            this.tableLayoutPanel2.PerformLayout();
            this.tableLayoutPanel3.ResumeLayout(false);
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.TableLayoutPanel tableLayoutPanel1;
        private System.Windows.Forms.DataGridView childDataGridView;
        private System.Windows.Forms.DataGridView parentDataGridView;
        private System.Windows.Forms.GroupBox opsGroupBox;
        private System.Windows.Forms.TableLayoutPanel tableLayoutPanel2;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.TextBox formationTextBox;
        private System.Windows.Forms.TextBox dateTextBox;
        private System.Windows.Forms.TextBox trophyTextBox;
        private System.Windows.Forms.TableLayoutPanel tableLayoutPanel3;
        private System.Windows.Forms.Button opsBtn;
        private System.Windows.Forms.Button updateDatabaseBtn;
        private System.Windows.Forms.Button connectBtn;
    }
}

