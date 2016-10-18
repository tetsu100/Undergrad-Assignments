<%@ Control Language="c#" AutoEventWireup="false" Codebehind="GoogleIt.ascx.cs" Inherits="GoogleWebServices.GoogleIt" TargetSchema="http://schemas.microsoft.com/intellisense/ie5"%>
<script language="JavaScript" src="calendar2.js"></script>
<P>&nbsp;</P>
<P>
	<TABLE id="Table1" style="WIDTH: 531px; HEIGHT: 138px" cellSpacing="1" cellPadding="1"
		width="531" align="center" border="1">
		<TR>
			<TD><asp:label id="Label1" Font-Bold="True" runat="server">Google Search</asp:label></TD>
			<TD><asp:textbox id="txtBasicSearch" runat="server" Width="296px"></asp:textbox></TD>
		</TR>
		<TR>
			<TD><asp:label id="Label2" Font-Bold="True" runat="server">Restricted Site (Optional)</asp:label></TD>
			<TD><asp:textbox id="txtSite" runat="server" Width="296px"></asp:textbox></TD>
		</TR>
		<TR>
			<TD><asp:label id="Label3" Font-Bold="True" runat="server">Filter</asp:label>&nbsp;<STRONG>(Optional)</STRONG></TD>
			<TD><asp:textbox id="txtFilter" runat="server" Width="296px"></asp:textbox></TD>
		</TR>
		<tr>
			<td>&nbsp;<STRONG>From Date (Optional)</STRONG></td>
			<td><INPUT type="text" name="txtDateFrom"> <A href="javascript:CalendarFrom.popup();"><IMG height="16" alt="Click here to select the start date and time for the search" src="img/cal.gif"
						width="16" border="0"></A>
			</td>
		</tr>
		<tr>
		</tr>
		<tr>
			<td style="HEIGHT: 30px">&nbsp;<STRONG>To Date (Optional)</STRONG></td>
			<td style="HEIGHT: 30px"><INPUT type="text" name="txtDateTo"> <A href="javascript:CalendarTo.popup();">
					<IMG height="16" alt="Click here to select the end date and time for the search" src="img/cal.gif"
						width="16" border="0"></A><br>
			</td>
		</tr>
		<TR>
			<TD></TD>
			<TD><asp:button id="btnSearch" runat="server" Width="72px" Text="Search"></asp:button></TD>
		</TR>
	</TABLE>
</P>
<P><asp:label id="lblError" Font-Bold="True" runat="server" Height="16px" Font-Size="Large" ForeColor="Red">[lblError]</asp:label></P>
<P><asp:label id="lblResults" Font-Bold="True" runat="server" Font-Size="Medium">[lblResults]</asp:label></P>
<P><asp:datagrid id="dgResults" runat="server" Width="100%" HorizontalAlign="Left" CellPadding="4"
		BorderWidth="1px" BorderStyle="None" BorderColor="#CC9966" BackColor="White">
		<SelectedItemStyle Font-Bold="True" ForeColor="#663399" BackColor="#FFCC66"></SelectedItemStyle>
		<ItemStyle ForeColor="#330099" BackColor="White"></ItemStyle>
		<HeaderStyle Font-Underline="True" Font-Bold="True" ForeColor="#FFFFCC" BackColor="#990000"></HeaderStyle>
		<FooterStyle ForeColor="#330099" BackColor="#FFFFCC"></FooterStyle>
		<PagerStyle HorizontalAlign="Center" ForeColor="#330099" BackColor="#FFFFCC"></PagerStyle>
	</asp:datagrid></P>
<script language="javascript">
	var CalendarFrom = new calendar2(document.forms(0).elements['txtDateFrom']);
	CalendarFrom.year_scroll = false;
	CalendarFrom.time_comp = false;
	var CalendarTo = new calendar2(document.forms(0).elements['txtDateTo']);
	CalendarTo.year_scroll = false;
	CalendarTo.time_comp = false;
	<asp:PlaceHolder id="JavaScriptInit" runat="server"></asp:PlaceHolder>
	
</script>
