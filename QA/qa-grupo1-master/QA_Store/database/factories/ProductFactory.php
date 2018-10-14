<?php

use Faker\Generator as Faker;
use QA_Store\Product;
$factory->define(QA_Store\Product::class, function (Faker $faker) {
    $categories = QA_Store\Category::all()->pluck('id')->toArray();
    return [
        'name' => $faker->company,
        'Description' => $faker->text($maxNbChars = 200),
        'Available' => $faker->boolean,
        'Price' => $faker->numberBetween($min = 10, $max = 60),
        'Inventory'=> $faker->numberBetween($min = 1, $max = 15),
        'idCategory'=> $faker->randomElement($categories),
    ];
});
