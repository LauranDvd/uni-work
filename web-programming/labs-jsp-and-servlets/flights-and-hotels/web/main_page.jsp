<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<!DOCTYPE html>
<html>
<head>
    <meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
    <title>Insert title here</title>
    <link rel="stylesheet" href="styles.css"/>
    <script src="js/jquery-2.0.3.js"></script>
    <script src="js/main-page-script.js?<%= System.currentTimeMillis() %>"></script>
</head>
<body>
<%
    String name = (String) session.getAttribute("name");
    String date = (String) session.getAttribute("date");
    String city = (String) session.getAttribute("city");

    if (name == null || "".equals(name)) {
        out.println("You dont have a name. You cant enter the site");
    } else {
        out.println("Welcome, " + name + "<br/>");
        out.println("Date looked for: " + date + "<br/>");
        out.println("City looked for: " + city + "<br/>");
%>
<script>
    console.log('will set name');
    sessionStorage.setItem("name", "<%= name %>");
    console.log('did set name');
    sessionStorage.setItem("date", "<%= date %>");
    console.log('did set date');
    sessionStorage.setItem("city", "<%= city %>");
    console.log('did set city');
</script>

<navbar>
    <button onclick="$('#hotels-page-container').hide(); $('#flights-page-container').show(); updateFlightList();">Flights</button>
    <button onclick="$('#flights-page-container').hide(); $('#hotels-page-container').show(); updateHotelList();">Hotels</button>
</navbar>
<div id="flights-page-container">
    <h2>Flights stuff</h2>
    <table id="flightsTable">

    </table>
    <br/>
</div>
<div id="hotels-page-container" style="display: none;">
    <h2>Hotels stuff</h2>
    <table id="hotelsTable">

    </table>
    <br/>
</div>

<br/>

<button onclick="cancelAllReservations()">Cancel all reservations</button>

<button id="logoutButton">Exit reservation session</button>

<%
    }
%>

</body>
</html>