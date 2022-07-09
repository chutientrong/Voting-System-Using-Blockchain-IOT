
<?php
session_start();
if (!isset($_SESSION['Admin-name'])) {
  header("location: login.php");
}
// Include the function file
include 'poll_function.php';
// Connect to MySQL
$pdo = pdo_connect_mysql();
// MySQL query that retrieves all the polls and poll answers
$stmt = $pdo->query('SELECT p.*, GROUP_CONCAT(pa.title ORDER BY pa.id) AS answers FROM polls p LEFT JOIN poll_answers pa ON pa.poll_id = p.id GROUP BY p.id');
$polls = $stmt->fetchAll(PDO::FETCH_ASSOC);
?>
<!DOCTYPE html>
<html>
<head>
    <title>Users</title>
    <meta charset="utf-8">
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <link rel="icon" type="image/png" href="icons/atte1.jpg">

    <script type="text/javascript" src="js/jquery-2.2.3.min.js"></script>
    <script type="text/javascript" src="js/bootstrap.js"></script>
    <link rel="stylesheet" type="text/css" href="css/Users.css">
    <script>
      $(window).on("load resize ", function() {
        var scrollWidth = $('.tbl-content').width() - $('.tbl-content table').width();
        $('.tbl-header').css({'padding-right':scrollWidth});
    }).resize();
    </script>
</head>
<body>
<?php include'header.php'; ?> 
<?=template_header('Polls')?>
<main>


<div class="content home">
	<h2 class="slideInDown animated">Polls</h2>
	<p>Welcome to the home page! You can view the list of polls below.</p>
	<a href="create_vote.php" class="create-poll slideInRight animated">Create Poll</a>
    <div class="slideInRight animated">	
        <table>
            <thead>
                <tr>
                    <td>#</td>
                    <td>Title</td>
                    <td>Candidates</td>
                    <td></td>
                </tr>
            </thead>
            <tbody>
                <?php foreach($polls as $poll): ?>
                <tr>
                    <td><?=$poll['id']?></td>
                    <td><?=$poll['title']?></td>
                    <td><?=$poll['answers']?></td>
                    <td class="actions">
                        <a href="vote.php?id=<?=$poll['id']?>" class="view" title="View Poll"><i class="fas fa-eye fa-xs"></i></a>
                        <a href="delete.php?id=<?=$poll['id']?>" class="trash" title="Delete Poll"><i class="fas fa-trash fa-xs"></i></a>
                    </td>
                </tr>
                <?php endforeach; ?>
            </tbody>
        </table>
    </div>
</div>
</main>
</body>
<?=template_footer()?>

</html>