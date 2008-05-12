<?php

getpost_ifset(array('id', 'title', 'id_component','description','priority','creator','username' ));

if (($form_action=='ask-edit') || ($form_action=='ask-add') || ($form_action=='add') || ($form_action=='edit') || ($form_action=='ask-delete') || ($form_action=='delete')){
	 $HD_Form = new FormHandler("cc_ticket","Ticket");
}else {

   $HD_Form = new FormHandler("cc_ticket, cc_card", "Ticket");
}




$HD_Form -> FG_DEBUG = 0;
$HD_Form -> FG_TABLE_DEFAULT_ORDER = " id";
$HD_Form -> FG_TABLE_DEFAULT_SENS = "DESC";
$HD_Form -> FG_TABLE_CLAUSE = " cc_card.id=creator ";
$HD_Form -> FG_TABLE_ID="cc_ticket.id";



$priority_list = array();
$priority_list["0"] = array( gettext("NONE"), "0");
$priority_list["1"] = array( gettext("LOW"), "1");
$priority_list["2"] = array( gettext("MEDIUM"), "2");
$priority_list["3"] = array( gettext("HIGH"), "3");


$HD_Form -> AddViewElement(gettext("ID"), "id", "5%", "center", "sort");
$HD_Form -> AddViewElement(gettext("HOLDER"), "creator", "10%", "center", "sort", "25", "lie", "cc_card", "lastname, firstname", "id='%id'", "%1 %2");
$HD_Form -> AddViewElement(gettext("CARDNUMBER"), "username", "12%", "center", "sort", "", "30", "", "", "", "", "linktocustomer");
$HD_Form -> AddViewElement(gettext("TITLE"), "title", "20%", "center", "sort");
$HD_Form -> AddViewElement(gettext("CREATIONDATE"), "creationdate", "15%", "center", "sort", "19", "", "", "", "", "", "display_dateformat");
$HD_Form -> AddViewElement(gettext("COMPONENT"), "id_component", "10%", "center", "sort", "15", "lie", "cc_support_component", "name", "id='%id'", "%1");
$HD_Form -> AddViewElement(gettext("PRIORITY"), "priority", "10%", "center", "sort", "", "list", $priority_list);

$HD_Form -> FieldViewElement ('cc_ticket.id, creator, username, title, cc_ticket.creationdate, id_component , priority');


$HD_Form -> FG_OTHER_BUTTON1_LINK = "CC_ticket_view.php?id=";
$HD_Form -> FG_OTHER_BUTTON1_IMG = Images_Path."/icon-viewdetails.gif";


$HD_Form -> CV_NO_FIELDS  = gettext("THERE IS NO")." ".strtoupper($HD_Form->FG_INSTANCE_NAME)." ".gettext("CREATED!");
$HD_Form -> CV_DISPLAY_LINE_TITLE_ABOVE_TABLE = false;
$HD_Form -> CV_TEXT_TITLE_ABOVE_TABLE = '';
$HD_Form -> CV_DISPLAY_FILTER_ABOVE_TABLE = false;

$HD_Form -> FG_OTHER_BUTTON1 = true;
$HD_Form -> FG_EDITION = true;
$HD_Form -> FG_DELETION = true;

if ($form_action=='ask-add'){
	$DBHandle_max  = DbConnect();
	if ($username) {
		$resmax = $DBHandle_max -> Execute("SELECT id FROM cc_card where username='$username'");
		$numrow = 0;
		if ($resmax)
			$numrow = $resmas -> RecordCount( );

		if ($numrow!=0) {
			$db_row [] = $resmax -> fetchRow();
			$val_default = "value='".$db_row[0][0]."'";
		}
	}
}

$HD_Form -> AddEditElement (gettext("CREATOR"),
	"creator",
	'',
	"POPUPVALUE",
	"size=30 maxlength=50 $val_default",
	"4",
	gettext("Insert the Id CardNumber"),
	"" , "", "", "", "",
	"A2B_entity_card.php?popup_select=1&"
	, ", 'CardNumberSelection','width=550,height=350,top=20,left=100,scrollbars=1'" ,
	gettext("Set the Card Number ID"));


$HD_Form -> AddEditElement (gettext("TITLE"),
	"title",
	'$value',
	"INPUT",
	"size=60 maxlength=50",
	"9",
	gettext("Insert the Title of ticket "),
	"" , "", "", "", "", "", "", "" );
$HD_Form -> AddEditElement (gettext("COMPONENT"),
			   "id_component",
			   "",
			   "SELECT",
			   "", "", "",
			   "sql",
			   "cc_support_component",
			   "name, id",
			   "", "", "%1", "", "");

$HD_Form -> AddEditElement (gettext("PRIORITY"),
	"priority",
	'$value',
	"SELECT",
	"",
	"",
	"",
	"list" , "", "", "", $priority_list, "%1", "", "");

$HD_Form -> AddEditElement (gettext("DESCRIPTION"),
	"description",
	'',
	"TEXTAREA",
	"cols=50 rows=4",
	"",
	gettext("Insert the description"),
	"" , "", "", "", "" , "", "", "");





$HD_Form -> FieldEditElement (' creator, title, id_component, priority, description');

if (DB_TYPE == "postgres") {
	$HD_Form -> FG_QUERY_ADITION_HIDDEN_FIELDS = "";
	$HD_Form -> FG_QUERY_ADITION_HIDDEN_VALUE  = "";
}else{
	$HD_Form -> FG_QUERY_ADITION_HIDDEN_FIELDS = "creationdate ";
	$HD_Form -> FG_QUERY_ADITION_HIDDEN_VALUE  = "now()";
}



$HD_Form -> FG_INTRO_TEXT_EDITION= '';
$HD_Form -> FG_INTRO_TEXT_ASK_DELETION = gettext("If you really want remove this")." ".$HD_Form->FG_INSTANCE_NAME.", ".gettext("click on the delete button.");
$HD_Form -> FG_INTRO_TEXT_ADD = gettext("you can add easily a new")." ".$HD_Form->FG_INSTANCE_NAME.".<br>".gettext("Fill the following fields and confirm by clicking on the button add.");


$HD_Form -> FG_INTRO_TEXT_ADITION = '';
$HD_Form -> FG_TEXT_ADITION_CONFIRMATION = gettext("Your new")." ".$HD_Form->FG_INSTANCE_NAME." ".gettext("has been inserted.")."<br>";

$HD_Form -> FG_BUTTON_EDITION_SRC = $HD_Form -> FG_BUTTON_ADITION_SRC  = Images_Path . "/cormfirmboton.gif";
$HD_Form -> FG_BUTTON_EDITION_BOTTOM_TEXT = $HD_Form -> FG_BUTTON_ADITION_BOTTOM_TEXT = gettext("Click 'Confirm Data' to continue");

$HD_Form -> FG_GO_LINK_AFTER_ACTION_ADD = $_SERVER['PHP_SELF']."?atmenu=document&stitle=Document&wh=AC&id=";
$HD_Form -> FG_GO_LINK_AFTER_ACTION_EDIT = $_SERVER['PHP_SELF']."?atmenu=document&stitle=Document&wh=AC&id=";
$HD_Form -> FG_GO_LINK_AFTER_ACTION_DELETE = $_SERVER['PHP_SELF']."?atmenu=document&stitle=Document&wh=AC&id=";
?>