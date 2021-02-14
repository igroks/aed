import scala.collection.mutable.ArrayBuffer

object Main{

    def insertionSort(vet: ArrayBuffer[Int]): Unit = {

        for(j <- 1 until vet.length){

            var pivot = vet(j)
            var i = j-1

            while((i >= 0) && (vet(i) > pivot)){
                vet(i+1) = vet(i)
                i -= 1;
            }
            vet(i+1) = pivot
        }
    }

    def main(args: Array[String]): Unit = {
        
        //Exemplo
        val vet = ArrayBuffer(4,2,7,5,1,9,3,8,6)
        insertionSort(vet)
        println(vet)
    }
}