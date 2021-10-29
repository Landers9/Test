<?php 
    $som = 0;
    $nbr = $argv[1];
    for($i=0; $i< $nbr; $i++){
        $mult3 = 3*$i;
        if ($mult3 >= $nbr){
            for($j=0; $j< $nbr; $j++){
                $mult5 = 5*$j;
                if($mult5 >= $nbr){
                    break;
                }

                else{
                    $som = $som + $mult5
                }
            }
        }

        else{
            $som = $som + $mult3;
        }
    }

    echo $som;
?>