<%@ page import="webubb.domain.User" %>
<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<!DOCTYPE html>
<html>
<head>
    <meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
    <title>Insert title here</title>
    <link rel="stylesheet" href="styles.css"/>
    <script src="js/jquery-2.0.3.js"></script>
    <script src="js/main-page-script.js"></script>
</head>
<body>
<%! User user; %>
<% user = (User) session.getAttribute("user");
    if (user == null || user.getUsername().isEmpty()) {
        out.println("Bad credentials!");
    } else {
        out.println("Welcome, " + user.getUsername());
%>
<script>
    sessionStorage.setItem("userId", <% out.println(user.getUserId()); %>)
</script>

<br/><br/>
<label for="noPicsToLoad">Number of pics to load:</label> <br/>
<input type="number" min="1" name="noPicsToLoad" id="noPicsToLoad">
<br/>
<button id="loadPics">Load</button>
<br/><br/>
<table id="picturesTable">

</table>
<br/>

Add a new picture:
<form method="post" action="PicturesController" enctype="multipart/form-data" id="uploadPicSection">
    <input type="file" name="uploadedPic" id="uploadedPic" accept="image/png, image/jpeg, image/jpg">
    <input type="submit" value="Upload">
</form>
<br/><Br/>
<button id="logoutButton">Logout</button>

<%
    }
%>

</body>
</html>