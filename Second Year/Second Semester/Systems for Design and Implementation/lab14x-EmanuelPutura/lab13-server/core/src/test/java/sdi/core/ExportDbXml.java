package sdi.core;

import org.dbunit.database.DatabaseConnection;
import org.dbunit.database.IDatabaseConnection;
import org.dbunit.dataset.IDataSet;
import org.dbunit.dataset.xml.FlatXmlDataSet;

import java.io.FileOutputStream;
import java.sql.Connection;
import java.sql.DriverManager;

public class ExportDbXml {
    public static void main(String[] args) throws Exception
    {
        String jdbcURL = "jdbc:postgresql://localhost:5432/workshop";
        String user = "postgres";
        String password = "postgres";

        // database connection
        Connection jdbcConnection = DriverManager.getConnection(jdbcURL, user, password);
        IDatabaseConnection connection = new DatabaseConnection(jdbcConnection);

        // full database export
        IDataSet fullDataSet = connection.createDataSet();
        FlatXmlDataSet.write(fullDataSet, new FileOutputStream("full.xml"));
    }
}
