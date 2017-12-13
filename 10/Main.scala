import scala.annotation.tailrec

object Main {
  def main(args: Array[String]): Unit = {
    doProblem()
    doProblemPart2()
  }

  def doProblem(): Unit = {
    val lines = scala.io.Source.fromFile("input.txt", "utf-8").getLines().reduceLeft(_ + _)
    val values = (0 until 256)
    val output = hash((0 until 256), 0, 0, lines.split(",\\s*").map(s => Integer.parseInt(s)))

    println(
      output.head * (output.tail.head)
    )
  }

  def doProblemPart2(): Unit = {
    val bytes = scala.io.Source.fromFile("input.txt", "ASCII").iter.map(c => c & 0xFF).toList ++ List(17, 31, 73, 47, 23)

    val sparseHash = hash((0 until 256), 0, 0, bytes, 64)
    val denseHash = sparseHash.grouped(16).map(t => t.reduce(_ ^ _)).toList

    println(sparseHash)
    println(denseHash.map(i => {
      val mapped = Integer.toHexString(i)
      if (mapped.size != 2) {
        "0" + mapped
      } else {
        mapped
      }
    }).reduceLeft(_ + _))
  }

  def max(a: Int, b: Int) = Math.max(a, b)

  def min(a: Int, b: Int) = Math.min(a, b)

  def invertListSlow(list: Seq[Int], position: Int, len: Int): Seq[Int] = {
    if (len == 0 || len == 1) return list

    val swaps = (0 until len).map(t => (position + t, position + len - t - 1)).map(t => (t._1 % list.size, t._2 % list.size)).toMap

    return list.indices.map(s => swaps.getOrElse(s, s)).map(t => list(t))
  }

  @tailrec
  def hash(list: Seq[Int], position: Int, skipsize: Int, length: Seq[Int], rounds: Int): Seq[Int] = {
    if (rounds == 0) {
      return list
    } else {
      val (newlist, newPosition, newskipSize) = hashPreserving(list, position, skipsize, length)
      return hash(newlist, newPosition, newskipSize, length, rounds - 1)
    }
  }

  @tailrec
  def hashPreserving(list: Seq[Int], position: Int, skipsize: Int, length: Seq[Int]): (Seq[Int], Int, Int) = {
    if (length.isEmpty) return (list, position, skipsize)

    val len = length.head
    val inverted = invertListSlow(list, position, length.head)
    val nextPosition = (position + skipsize + length.head) % list.size
    val nextSkipsize = skipsize + 1
    hashPreserving(inverted, nextPosition, nextSkipsize, length.tail)
  }

  @tailrec
  def hash(list: Seq[Int], position: Int, skipsize: Int, length: Seq[Int]): Seq[Int] = {
    if (length.isEmpty) return list

    val len = length.head
    val inverted = invertListSlow(list, position, length.head)
    val nextPosition = (position + skipsize + length.head) % list.size
    val nextSkipsize = skipsize + 1
    hash(inverted, nextPosition, nextSkipsize, length.tail)
  }
}

