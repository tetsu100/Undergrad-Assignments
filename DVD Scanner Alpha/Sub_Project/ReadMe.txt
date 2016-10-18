"Use Google APIs in .NET" by Vijay Mehta
Visual Studio Magazine, July 2005

The GoogleWebServices solution is a fully functional .NET user control that 
can be used to access the Google Web API's for:  Basic Google Searching, Site 
Restricted Google Searching, Date Restricted Google Searching, and File Format Google
Searching.  

Contents of GoogleWebServices.sln:
1. GoogleIt.ascx & GoogleIt.ascx.cs - The actual .Net Control
2. WebForm1.aspx - A web form with the control applied
3. calendar.html & calendar.js - Javascript popup calendar used for date selection when doing date restricted Google searches
4. \img - various images used for the popup calendar

Setup:
1. Copy the web project named GoogleWebServices to your c:\inetpub\wwwroot\ directory and convert that into a virtual directory using IIS MMC.
2. Register with Google to receive a license key to use their API's (http://www.google.com/apis)
3. After receiving the license key insert it in the "LICENSE_KEY" constant contained in the GoogleIt.ascx.cs file
4. Run the solution