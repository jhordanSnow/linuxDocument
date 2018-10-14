<?php

use Illuminate\Database\Seeder;

class DatabaseSeeder extends Seeder
{
    /**
     * Seed the application's database.
     *
     * @return void
     */
    public function run()
    {
        // $this->call(CategoryFactory::class);
        $categories = factory(QA_Store\Product::class, 100)->create();
    }
}
