<?php
class model{
function get_title(){
return "Stupid Servey";
}

function get_form_data(){
return array(array(
"First Name:",
"text",
array(
"id" =>"bcode",
"name" =>"bcode",
"class" =>"form-control"
)),

array(
"Last Name:",
"text",
array(
"id" =>"bdesc",
"name" =>"bdesc",
"class" =>"form-control"
)),

array(
"Weight:",
"text",
array(
"id" =>"bdest",
"name" =>"bdest",
"class" =>"form-control"
)),

array(
"Age:",
"text",
array(
"id" =>"fname",
"name" =>"fname",
"class" =>"form-control"
)),

array(
"Kevin:",
"text",
array(
"id" =>"fname",
"name" =>"fname",
"class" =>"form-control"
)));
}


}
class view{


	function get_html($tag, $text, $info=""){
		return "<$tag $info>\n$text\n</$tag>\n";
	}


	function get_input_box($attributes){
		$info = "";
		foreach ($attributes as $att => $key){
			$info .= $att . "=\"" . $key . "\" ";
		}
		return "<input $info/>\n";
	}

  function print_header($title){
    $head = "
    <!--Start of head -->
    <!DOCTYPE html PUBLIC \"-//W3C//DTD XHTML 1.0 Strict//EN\"
            \"http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd\">
    <html xmlns=\"http://www.w3.org/1999/xhtml\">
    	<head>
    		<title>$title</title>
    		<link rel=\"stylesheet\" href=\"https://maxcdn.bootstrapcdn.com/bootstrap/3.3.5/css/bootstrap.min.css\">
    		<link rel=\"stylesheet\" href=\"https://maxcdn.bootstrapcdn.com/bootstrap/3.3.5/css/bootstrap-theme.min.css\">
    		<script src=\"https://ajax.googleapis.com/ajax/libs/jquery/1.11.3/jquery.min.js\"></script>
    		<script src=\"https://maxcdn.bootstrapcdn.com/bootstrap/3.3.5/js/bootstrap.min.js\"></script>
    		<meta http-equiv=\"Content-Type\" content=\"text/html; charset=iso-8859-1\" />
    	</head>\n<!-- End of head -->\n\n";
      echo $head;
  }
	function get_form_element($title, $type, $value){
		switch($type){
			case "text":
				$label = $this->get_html("label", $title);
				$input = $this->get_input_box($value);

				$form_element = $this->get_html(
					"div",
					$label . $input,
					"class =\"form-group\""
				);
				break;

			case "radio":
				$label = $this->get_html("label", $title, "for=\"$name\"");
				$input ="";
				foreach ($value as $val ) {
					$radio = $this->get_input_box($val).$val['value'];
					$radio = $this->get_html("label", $radio);
					$input .= $this->get_html("div", $radio, "class=\"radio\"");
				}


				$form_element = $this->get_html(
					"div",
					$input,
					"class =\"form-group\""
				);
				break;

			case "hidden":
			$input = $this->get_input_box($value);

			$form_element = $this->get_html(
				"div",
				$input,
				"class =\"form-group\""
			);
			break;
		}
		return $form_element;
	}

	function generate_form($title, $form_data, $error=""){

		$form = $this->get_html("h2", $title);
		foreach ($form_data as $form_element) {
			if($error != ""){
				foreach ($error as $key => $val) {

					if($key == $form_element[2]){
						$form .=$this->get_html("p", $val, "class=\"text-danger\"");
					}
				}
			}

			$form .= $this->get_form_element(
				$form_element[0],
				$form_element[1],
				$form_element[2]
			);
		}
		$form .= $this->get_html("button", "Submit","type=\"button\" name=\"submit\" class=\"btn btn-default\" id=\"submitbutton\" ");
		$form = $this->get_html("form", $form, "action=\"\" method=\"post\" id=\"form\"");
		$form = $this->get_html("div", $form, "class=\"container-fluid\"");
		$form = $this->get_html("div", $form, "class=\"row\"");
		$form = $this->get_html("div", $form, "class=\"col-xs-6 col-md-4\"");

		$form = $this->get_html("body", $form, "class = \"container\"");

		echo $form;
	}

}

class controller{
  /*Main Function*/
  function main(){


    $model = new model;
    $view = new view;

      $view->print_header($model->get_title());
	    $view->generate_form(
				$model->get_title(),
				$model->get_form_data()
			);
		}
  }

$controller = new controller;
$controller->main();
