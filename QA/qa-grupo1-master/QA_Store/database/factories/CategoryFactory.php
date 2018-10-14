<?php

use Faker\Generator as Faker;
use QA_Store\Category;

$factory->define(QA_Store\Category::class, function (Faker $faker) {
    return [
        'Name' => $faker->company,
        'Description' => $faker->text($maxNbChars = 200),
        'Available' => $faker->boolean,
    ];
});

