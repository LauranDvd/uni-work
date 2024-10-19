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
<% String name = (String) session.getAttribute("name");
    if (name == null || "".equals(name)) {
        out.println("You dont have a name. You (for now) cant enter the site. Maybe well change this...");
    } else {
        out.println("Welcome, " + name);
%>
<script>
    sessionStorage.setItem("name", <% out.println(name); %>)
</script>

<br/><br/>
<label for="journalName">Journal name:</label> <br/>
<input type="text" name="journalName" id="journalName">
<br/>
<button id="getArticles">Get articles</button>
<br/><br/>
<table id="articlesTable">

</table>
<br/>

Add a new article:
<form method="post" action="ArticlesController" enctype="multipart/form-data" id="articleForm">
    <input type="text" name="journalName" placeholder="journal name">
    <textarea name="summary" placeholder="summary"></textarea>
    <input type="submit" value="Upload">
</form>
<br/><Br/>
<button id="logoutButton">Logout</button>

<br/>
New articles from others:
<table id="notification-div">
    <tr style='background-color: mediumseagreen'>
        <td>User</td>
        <td>Journal</td>
        <td>Summary</td>
        <td>Date</td>
    </tr>
</table>

<%
    }
%>

</body>
</html>