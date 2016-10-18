namespace GoogleWebServices
{
	using System;
	using System.Data;
	using System.Drawing;
	using System.Web;
	using System.Web.UI.WebControls;
	using System.Web.UI.HtmlControls;
	using System.Web.Services;
	using com.google.api;
	using System.Collections;
	using System.Text;
	using System.Diagnostics;
	using System.Globalization;

	/// <summary>
	///		This purpose of this control is to demonstrate some of the functionality of the Google Web API, and show
	///		you how to search against Google's 8billion+ web pages.
	///		The control does:
	///			1. Basic Search
	///			2. Site Restricted Search
	///			3. File Format Filter Search
	///			4. Date Restricted Search
	///			5. Any combination of the above
	/// </summary>
	public class GoogleIt : System.Web.UI.UserControl
	{
		protected System.Web.UI.WebControls.TextBox txtBasicSearch;
		protected System.Web.UI.WebControls.Button btnSearch;
		protected System.Web.UI.WebControls.DataGrid dgResults;
		protected System.Web.UI.WebControls.Label lblError;
		protected System.Web.UI.WebControls.Label Label1;
		protected System.Web.UI.WebControls.Label Label2;
		protected System.Web.UI.WebControls.TextBox txtSite;
		protected System.Web.UI.WebControls.Label Label3;
		protected System.Web.UI.WebControls.TextBox txtFilter;
		protected System.Web.UI.WebControls.Label lblResults;
		protected System.Web.UI.WebControls.Label Label4;
		
		/* *******************************************
		 * THIS PROGRAM WILL NOT FUNCTION UNLESS YOU REGISTER
		 * WITH GOOGLE AND RECEIVE A VALID LICENSE KEY.
		 * PLEASE INSERT YOUR VALID LICENSE KEY IN THE CONSTANT
		 * BELOW.
		 * *********************************************
		 */ 
		private const string LICENSE_KEY = "Your License Key Here!";
		
		/// <summary>
		/// Page Load -> set label's visible property to false
		/// </summary>
		/// <param name="sender"></param>
		/// <param name="e"></param>
		private void Page_Load(object sender, System.EventArgs e)
		{
			// Put user code to initialize the page here
			lblError.Visible = false;
			lblResults.Visible = false;
		}

		#region Web Form Designer generated code
		override protected void OnInit(EventArgs e)
		{
			//
			// CODEGEN: This call is required by the ASP.NET Web Form Designer.
			//
			InitializeComponent();
			base.OnInit(e);
		}
		
		/// <summary>
		///		Required method for Designer support - do not modify
		///		the contents of this method with the code editor.
		/// </summary>
		private void InitializeComponent()
		{
			this.btnSearch.Click += new System.EventHandler(this.btnSearch_Click);
			this.Load += new System.EventHandler(this.Page_Load);

		}
		#endregion

		/// <summary>
		/// Code for the search button click event.  Calls ths GoogleHandler and handles errors 
		/// </summary>
		/// <param name="sender"></param>
		/// <param name="e"></param>
		private void btnSearch_Click(object sender, System.EventArgs e)
		{
			try 
			{
				GoogleHandler();
			}
			catch (System.Web.Services.Protocols.SoapException ex) 
			{
				ShowErrorMessage(ex.ToString(), true);
			}
			catch (System.Exception ex)
			{
				ShowErrorMessage(ex.ToString(),true);
			}
		}
		
		/// <summary>
		/// This is the main interface, which calls all of the 
		/// helper methods.  We create the google objects, do the search, display the results inside
		/// this code.  
		/// </summary>
		private void GoogleHandler()
		{
			// Create a Google Search object
			GoogleSearchService gss = new GoogleSearchService();

			// Invoke the search method
			GoogleSearchResult results = gss.doGoogleSearch(LICENSE_KEY, BuildQuery(), 
				0, 10, false, string.Empty, false, string.Empty, string.Empty, string.Empty);
				
			// Extract the estimated number of results for the search and display it
			lblResults.Text = "Results Found: " + results.estimatedTotalResultsCount;
			lblResults.Visible = true;

			DataTable table = new DataTable();
			DataColumn col1 = new DataColumn("Results", typeof(string));

			table.Columns.Add(col1);

			int pointer = 0;
				
			while(pointer<results.resultElements.Length)
			{			
				DataRow row = table.NewRow();
				row[0] = FormatResults(results.resultElements[pointer]);
				table.Rows.Add(row);
				pointer ++;
			}

			dgResults.DataSource = table;
			dgResults.DataBind();
		
		}

		/// <summary>
		/// Helper method to display an error in the control
		/// </summary>
		/// <param name="msg">string</param>
		/// <param name="bShow">bool</param>
		private void ShowErrorMessage(string msg, bool bShow)
		{
			if (bShow == true)
			{
				lblError.Text = "<br>" + msg;
				lblError.Visible = true;
			}
			else
			{
				lblError.Visible = false;
			}
		}
		
		/// <summary>
		/// Helper method to build the query.
		/// </summary>
		/// <returns>string - query string used by the google api</returns>
		private string BuildQuery()
		{
			StringBuilder query = new StringBuilder();
			if(txtBasicSearch.Text.Length > 0)
				query.Append(txtBasicSearch.Text);
			else
				throw new Exception("You have to specify a basic search criteria");
			
			if(txtSite.Text.Length > 0)
			{
				query.Append(" site:");
				query.Append(txtSite.Text);
			}
			
			if(txtFilter.Text.Length > 0)
			{
				query.Append(" filetype:");
				query.Append(txtFilter.Text);
			}
			
			string txtDateFrom = Request.Form.Get("txtDateFrom");
			string txtDateTo = Request.Form.Get("txtDateTo");

			if(txtDateFrom.Length > 0 && txtDateTo.Length > 0)
			{
				string fromDateJul = GregToJulian(txtDateFrom);
				string toDateJul = GregToJulian(txtDateTo);

				query.Append(" daterange:");
				query.Append(fromDateJul);
				query.Append("-");
				query.Append(toDateJul);

			}

			return query.ToString();			
		
		}
		/// <summary>
		/// Helper method adapted from Neil Cowburn's blog (http://blog.opennetcf.org/ncowburn/)
		/// This method is used to change a Gregorian date to a Julian date.
		/// </summary>
		/// <param name="gregDate">string</param>
		/// <returns>string Julian Date</returns>
		private string GregToJulian(string gregDate)
		{
			DateTime dt = DateTime.Parse(gregDate);

			double A = Math.Floor(dt.Year/100);
			double B = Math.Floor(A/4);
			double C = 2 - A + B;
			double D = dt.Day;
			double E = Math.Floor(365.25*(dt.Year+4716));
			double F = Math.Floor(30.6001*(dt.Month+1));

			double JD = C+D+E+F-1524.5;
			return JD.ToString();
		}
		
		/// <summary>
		/// Helper Method which accepts a single GoogleSearchResult.ResultElement
		/// then formats the results into an html string
		/// </summary>
		/// <param name="resultToFormat">string</param>
		/// <returns>string - formated html results</returns>
		private string FormatResults(ResultElement resultToFormat)
		{
			
			StringBuilder sb = new StringBuilder();
			sb.Append("<p><b><u><a href=");
			sb.Append(resultToFormat.URL);
			sb.Append(" target=new>");
			sb.Append(resultToFormat.title);
			sb.Append("</a></u></b></p>");
			sb.Append("<p>");
			sb.Append(resultToFormat.snippet);
			sb.Append("<br>");
			sb.Append(resultToFormat.URL);
			sb.Append("&nbsp;");
			sb.Append(resultToFormat.cachedSize);
			sb.Append("</p>");			
			
			return sb.ToString();


		}
	}
}
